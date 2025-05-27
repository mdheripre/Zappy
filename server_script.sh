#!/bin/bash

PORT=4242
WIDTH=20
HEIGHT=20
CLIENTS=10
FREQ=100
AUTO_START="on"
DISPLAY_EGGS="true"
TEAMS=("team1" "team2")

SERVER_BINARY="./epitech_binary/zappy_server"

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
    --auto-start $AUTO_START \
    --display-eggs $DISPLAY_EGGS 
