#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4242
#define BUFFER_SIZE 1024

typedef struct {
    int sockfd;
} thread_args_t;

static void *read_from_server(void *arg)
{
    int sockfd = ((thread_args_t *)arg)->sockfd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(sockfd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("[SERVER] %s", buffer);
        fflush(stdout);
    }
    return NULL;
}

static void *write_to_server(void *arg)
{
    int sockfd = ((thread_args_t *)arg)->sockfd;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1)
        write(sockfd, line, strlen(line));
    free(line);
    return NULL;
}

static int setup_connection(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    if (sockfd < 0) {
        perror("socket");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int main(void)
{
    int sockfd = setup_connection();
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    pthread_t reader, writer;
    thread_args_t args;

    if (sockfd < 0)
        return 84;

    printf("Connected to %s:%d as GUI\n", SERVER_IP, SERVER_PORT);

    bytes_read = read(sockfd, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("[SERVER] %s", buffer);
    }

    write(sockfd, "GRAPHIC\n", 8);
    printf("Sent: GRAPHIC\n");

    args.sockfd = sockfd;
    pthread_create(&reader, NULL, read_from_server, &args);
    pthread_create(&writer, NULL, write_to_server, &args);

    pthread_join(reader, NULL);
    pthread_cancel(writer);

    close(sockfd);
    return 0;
}
