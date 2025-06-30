#!/bin/bash

# CONFIG
PORT=4242
WIDTH=10
HEIGHT=10
CLIENTS=10
FREQ=100
TEAMS=("team1" "team2")
SERVER_BINARY="./zappy_server"
AI_BINARY="../Zappy/zappy_ai"
GUI_BINARY="./zappy_gui"
AI_PER_TEAM=10
SERVER_IP="127.0.0.1"

PIDS=()  # Liste des PIDs lancés

# Fonction de nettoyage sur Ctrl+C
cleanup() {
    echo -e "\n[SHUTDOWN] Cleaning up all processes..."
    for pid in "${PIDS[@]}"; do
        if kill -0 "$pid" 2>/dev/null; then
            kill "$pid"
        fi
    done
    wait
    echo "[SHUTDOWN] Done."
    exit 0
}
trap cleanup SIGINT SIGTERM

# Build team arguments
TEAM_ARGS=()
for team in "${TEAMS[@]}"; do
    TEAM_ARGS+=("$team")
done

# Start server
$SERVER_BINARY \
    -p $PORT \
    -x $WIDTH \
    -y $HEIGHT \
    -n "${TEAM_ARGS[@]}" \
    -c $CLIENTS \
    -f $FREQ \
    -d &

SERVER_PID=$!
PIDS+=($SERVER_PID)
echo "[SERVER] Launched (PID: $SERVER_PID)"
sleep 1

# Start GUI in external terminal
if command -v gnome-terminal &> /dev/null; then
    gnome-terminal -- bash -c "$GUI_BINARY -p $PORT -h $SERVER_IP; exec bash" &
    GUI_PID=$!
elif command -v xterm &> /dev/null; then
    xterm -hold -e "$GUI_BINARY -p $PORT -h $SERVER_IP" &
    GUI_PID=$!
elif command -v konsole &> /dev/null; then
    konsole -e "$GUI_BINARY -p $PORT -h $SERVER_IP" &
    GUI_PID=$!
else
    echo "[ERROR] No terminal found for GUI."
    kill $SERVER_PID
    exit 1
fi
PIDS+=($GUI_PID)

echo "[GUI] Launched in external terminal (PID: $GUI_PID)"
echo "Waiting 5 seconds for GUI to connect..."
sleep 5

# Start AIs
for team in "${TEAMS[@]}"; do
    for ((i = 0; i < AI_PER_TEAM; i++)); do
        $AI_BINARY -h $SERVER_IP -n "$team" -p $PORT &
        AI_PID=$!
        PIDS+=($AI_PID)
        echo "[AI] Launched: team=$team instance=$i (PID: $AI_PID)"
    done
done

# Wait for server only; others are cleaned up via trap
wait $SERVER_PID
cleanup
