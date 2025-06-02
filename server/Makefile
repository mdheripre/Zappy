##
## EPITECH PROJECT, 2025
## B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
## File description:
## Makefile
##

NAME = zappy_server

SRC_DIR = src

SRC_SERVER = $(SRC_DIR)/Server
SRC_SERV_CTOR = $(SRC_SERVER)/constructor
SRC_SERV_DTOR = $(SRC_SERVER)/destructor
SRC_SERV_METHODS = $(SRC_SERVER)/methods
SRC_SERV_EVENT = $(SRC_SERVER)/events
SRC_CMD_MANAGER = $(SRC_DIR)/Command_Manager
SRC_CMD_MANAGER_CTOR = $(SRC_CMD_MANAGER)/constructor
SRC_CMD_MANAGER_DTOR = $(SRC_CMD_MANAGER)/destructor
SRC_CMD_MANAGER_METHODS = $(SRC_CMD_MANAGER)/methods
SRC_CMD_MANAGER_EVENTS = $(SRC_CMD_MANAGER)/events
SRC_CMD_MANAGER_EVENTS_IA = $(SRC_CMD_MANAGER_EVENTS)/ia
SRC_CMD_MANAGER_EVENTS_GUI = $(SRC_CMD_MANAGER_EVENTS)/gui
SRC_SHARED = $(SRC_DIR)/Shared
SRC_UTILS = $(SRC_DIR)/Utils
SRC_UTILS_QUEUE = $(SRC_UTILS)/Queue
SRC_UTILS_LOG = $(SRC_UTILS)/Log
SRC_UTILS_HELPERS = $(SRC_UTILS)/Helper
SRC_DISPATCHER = $(SRC_DIR)/Dispatcher
SRC_DISP_CTOR = $(SRC_DISPATCHER)/constructor
SRC_DISP_DTOR = $(SRC_DISPATCHER)/destructor
SRC_DISP_METHODS = $(SRC_DISPATCHER)/methods
SRC_LIST = $(SRC_DIR)/List
SRC_LIST_CTOR = $(SRC_LIST)/constructor
SRC_LIST_DTOR = $(SRC_LIST)/destructor
SRC_LIST_METHODS = $(SRC_LIST)/methods
SRC_GAME = $(SRC_DIR)/Game
SRC_GAME_CTOR = $(SRC_GAME)/constructor
SRC_GAME_DTOR = $(SRC_GAME)/destructor
SRC_GAME_METHODS = $(SRC_GAME)/methods

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_SERV_CTOR)/server_create.c \
	$(SRC_SERV_DTOR)/server_destroy.c \
	$(SRC_SERV_EVENT)/on_client_connected.c \
	$(SRC_SERV_EVENT)/on_event_not_found.c \
	$(SRC_SERV_EVENT)/on_identify_client.c \
	$(SRC_SERV_EVENT)/on_send_response.c \
	$(SRC_SERV_EVENT)/on_gui_init.c \
	$(SRC_SERV_EVENT)/on_ia_init.c \
	$(SRC_SERV_METHODS)/accept_client.c \
	$(SRC_SERV_METHODS)/get_delay.c \
	$(SRC_SERV_METHODS)/handle_poll.c \
	$(SRC_SERV_METHODS)/remove_client.c \
	$(SRC_SERV_METHODS)/server_run.c \
	$(SRC_SERV_METHODS)/broadcast_gui.c \
	$(SRC_SERV_METHODS)/setup_poll.c \
	$(SRC_CMD_MANAGER_CTOR)/command_manager_create.c \
	$(SRC_CMD_MANAGER_DTOR)/command_manager_destroy.c \
	$(SRC_CMD_MANAGER_METHODS)/command_manager_identify.c \
	$(SRC_CMD_MANAGER_METHODS)/command_manager_process_all.c \
	$(SRC_CMD_MANAGER_METHODS)/command_manager_register_all.c \
	$(SRC_CMD_MANAGER_EVENTS_IA)/forward.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/bct.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/msz.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/sgt.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/tna.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/mct.c \
	$(SRC_CMD_MANAGER_EVENTS)/not_found.c \
	$(SRC_SHARED)/shared.c \
	$(SRC_UTILS_LOG)/print_log.c \
	$(SRC_UTILS_HELPERS)/time.c \
	$(SRC_UTILS_HELPERS)/strip_linefeed.c \
	$(SRC_UTILS_QUEUE)/handle_queue.c \
	$(SRC_DISP_CTOR)/dispatcher_create.c \
	$(SRC_DISP_DTOR)/dispatcher_destroy.c \
	$(SRC_DISP_METHODS)/dispatcher_emit.c \
	$(SRC_DISP_METHODS)/dispatcher_register.c \
	$(SRC_LIST_CTOR)/list_create.c \
	$(SRC_LIST_DTOR)/list_destroy.c \
	$(SRC_LIST_METHODS)/list_clear.c \
	$(SRC_LIST_METHODS)/list_pop_front.c \
	$(SRC_LIST_METHODS)/list_push_back.c \
	$(SRC_LIST_METHODS)/list_size.c \
	$(SRC_GAME_CTOR)/game_create.c \
	$(SRC_GAME_DTOR)/game_destroy.c \
	$(SRC_GAME_METHODS)/game_add_event.c \
	$(SRC_GAME_METHODS)/game_pop_event.c \
	$(SRC_GAME_METHODS)/game_tick.c \
	$(SRC_GAME_METHODS)/dispatch_game_event.c \
	$(SRC_GAME_METHODS)/game_update.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -Iinclude

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
