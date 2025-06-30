#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4242
#define BUFFER_SIZE 1024

typedef struct {
    int sockfd;
} thread_args_t;

static long get_timestamp_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
}

static long last_sent_ms = 0;
static pthread_mutex_t chrono_lock = PTHREAD_MUTEX_INITIALIZER;

void *read_server_thread(void *arg)
{
    int sockfd = ((thread_args_t *)arg)->sockfd;
    char buffer[BUFFER_SIZE];
    ssize_t n;

    while ((n = read(sockfd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[n] = '\0';
        long now = get_timestamp_ms();

        pthread_mutex_lock(&chrono_lock);
        long delay = now - last_sent_ms;
        pthread_mutex_unlock(&chrono_lock);

        printf("[%.3f] [SERVER] %s", now / 1000.0, buffer);
        printf("[INFO] Roundtrip: %ld ms\n", delay);
        fflush(stdout);
    }
    return NULL;
}

void *write_input_thread(void *arg)
{
    int sockfd = ((thread_args_t *)arg)->sockfd;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        long now = get_timestamp_ms();

        pthread_mutex_lock(&chrono_lock);
        last_sent_ms = now;
        pthread_mutex_unlock(&chrono_lock);

        printf("[%.3f] [CLIENT] Sending: %s", now / 1000.0, line);
        write(sockfd, line, strlen(line));
    }

    free(line);
    return NULL;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        fprintf(stderr, "Usage: %s TEAM_NAME\n", av[0]);
        return 84;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    char buffer[BUFFER_SIZE] = {0};
    ssize_t n;

    if (sockfd < 0)
        return perror("socket"), 84;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return perror("connect"), 84;

    printf("Connected to %s:%d as AI\n", SERVER_IP, SERVER_PORT);

    n = read(sockfd, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("[SERVER] %s", buffer);
    }

    dprintf(sockfd, "%s\n", av[1]);

    for (int i = 0; i < 2; ++i) {
        memset(buffer, 0, sizeof(buffer));
        n = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (n > 0) {
            buffer[n] = '\0';
            printf("[SERVER] %s", buffer);
        }
    }

    pthread_t reader, writer;
    thread_args_t args = { .sockfd = sockfd };
    pthread_create(&reader, NULL, read_server_thread, &args);
    pthread_create(&writer, NULL, write_input_thread, &args);

    pthread_join(reader, NULL);
    pthread_cancel(writer);

    close(sockfd);
    return 0;
}
