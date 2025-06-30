import socket
import threading
import time
import argparse
import matplotlib.pyplot as plt
import random
import statistics

SERVER_HOST = 'localhost'
SERVER_PORT = 4242
TEAM_NAME = 'caca'

COMMANDS = [
    ('Forward\n', 7)
    # ('Left\n', 7),
    # ('Right\n', 7),
    # ('Look\n', 7)
]

RECEIVE_TIMEOUT = 10
REPEAT_COUNT = 10
CLIENT_STEPS = [10, 30, 50, 70, 90, 130, 170, 200]

class LatencyClient(threading.Thread):
    def __init__(self, f_value, results):
        super().__init__()
        self.f_value = f_value
        self.results = results

    def run(self):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(RECEIVE_TIMEOUT)
            sock.connect((SERVER_HOST, SERVER_PORT))

            sock.recv(1024)
            sock.sendall((TEAM_NAME + "\n").encode())
            sock.recv(1024)
            sock.recv(1024)

            for cmd, duration in COMMANDS:
                expected_latency = duration / self.f_value
                for _ in range(REPEAT_COUNT):
                    time.sleep(random.uniform(0.01, 0.05))
                    start = time.perf_counter()
                    sock.sendall(cmd.encode())
                    response = sock.recv(1024)
                    end = time.perf_counter()

                    if response.strip() == b'ok' or response.startswith(b'['):
                        elapsed = end - start
                        self.results.append((elapsed, expected_latency))
        except Exception:
            pass
        finally:
            try:
                sock.close()
            except:
                pass

def run_latency_test(f_value):
    x_clients = []
    y_diff = []
    y_success_ratio = []

    for n_clients in CLIENT_STEPS:
        results = []
        threads = [LatencyClient(f_value, results) for _ in range(n_clients)]
        for t in threads:
            t.start()
        for t in threads:
            t.join()

        if not results:
            print(f"Aucune donnée recueillie pour {n_clients} clients.")
            x_clients.append(n_clients)
            y_diff.append(None)
            y_success_ratio.append(0)
            continue

        latencies = [r[0] for r in results]
        expected_latencies = [r[1] for r in results]
        avg_latency = statistics.mean(latencies)
        avg_expected = statistics.mean(expected_latencies)
        diff = avg_latency - avg_expected

        margin = 1 / f_value
        errors_within_margin = sum(1 for r, e in results if abs(r - e) <= margin)
        success_ratio = (errors_within_margin / len(results)) * 100

        print(f"{n_clients} clients: latence mesurée = {avg_latency:.3f}s, attendue = {avg_expected:.3f}s, écart = {diff:.3f}s")

        x_clients.append(n_clients)
        y_diff.append(diff * 1000)
        y_success_ratio.append(success_ratio)

    return x_clients, y_diff, y_success_ratio, f_value

def plot_differences(x, y, success_ratio, f_value):
    expected_text = f"1 tick = {1/f_value:.3f}s"

    plt.figure(figsize=(10, 5))
    plt.plot(x, y, marker='o', label="Écart moyen", linewidth=2)
    plt.axhline(0, color='gray', linestyle='--', linewidth=1)
    plt.title(f"Écart de latence mesurée vs attendue\n({expected_text})", fontsize=14)
    plt.xlabel("Nombre de clients", fontsize=12)
    plt.ylabel("Écart de latence moyenne (ms)", fontsize=12)
    plt.xticks(x)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

    plt.figure(figsize=(10, 5))
    plt.plot(x, success_ratio, marker='x', color='green', label="Commandes dans la marge", linewidth=2)
    plt.title("Pourcentage de commandes dans la marge d'erreur (1 tick)", fontsize=14)
    plt.xlabel("Nombre de clients", fontsize=12)
    plt.ylabel("% de commandes acceptables", fontsize=12)
    plt.ylim(0, 105)
    plt.xticks(x)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Tester la latence réelle des commandes en fonction du nombre de clients")
    parser.add_argument('-f', type=int, required=True, help="valeur de f (fréquence du serveur)")
    args = parser.parse_args()

    x, y, success, f = run_latency_test(args.f)
    plot_differences(x, y, success, f)