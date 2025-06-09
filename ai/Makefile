##
## EPITECH PROJECT, 2025
## B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
## File description:
## Makefile
##

PROJECT_NAME := zappy_ai

DEBUG_BIN := target/debug/$(PROJECT_NAME)
RELEASE_BIN := target/release/$(PROJECT_NAME)

all: release

release:
	cargo build --workspace --release
	cp $(RELEASE_BIN) ./bin/

debug:
	cargo build --workspace
	cp $(DEBUG_BIN) ./zappy_ai_debug

clean:
	cargo clean
	rm -f ./zappy_ai ./zappy_ai_debug

fclean: clean

