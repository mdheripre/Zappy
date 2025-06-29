#!/bin/bash

PORT=4242
WIDTH=20
HEIGHT=20
CLIENTS=10
FREQ=10000
AUTO_START="on"
DISPLAY_EGGS="true"
TEAMS=("team1" "team2")

SERVER_BINARY="./zappy_server"

TEAM_ARGS=()
for team in "${TEAMS[@]}"; do
    TEAM_ARGS+=("$team")
done

$SERVER_BINARY \
    -p $PORT \
    -x $WIDTH \
    -y $HEIGHT \
    -n "${TEAM_ARGS[@]}" \
    -c $CLIENTS \
    -f $FREQ \
    -d
