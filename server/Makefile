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
SRC_SERV_METHODS_NET = $(SRC_SERV_METHODS)/Network
SRC_SERV_METHODS_EVT = $(SRC_SERV_METHODS)/Event
SRC_SERV_METHODS_CMDS = $(SRC_SERV_METHODS)/Commands
SRC_SHARED = $(SRC_DIR)/Shared
SRC_UTILS = $(SRC_DIR)/Utils
SRC_DISPATCHER = $(SRC_DIR)/Dispatcher
SRC_DISP_CTOR = $(SRC_DISPATCHER)/constructor
SRC_DISP_DTOR = $(SRC_DISPATCHER)/destructor
SRC_DISP_METHODS = $(SRC_DISPATCHER)/methods
SRC_LIST = $(SRC_DIR)/List
SRC_LIST_CTOR = $(SRC_LIST)/constructor
SRC_LIST_DTOR = $(SRC_LIST)/destructor
SRC_LIST_METHODS = $(SRC_LIST)/methods
SRC_CONFIG = $(SRC_DIR)/Config
SRC_CONFIG_CTOR = $(SRC_CONFIG)/constructor
SRC_CONFIG_DTOR = $(SRC_CONFIG)/destructor
SRC_CONFIG_METHODS = $(SRC_CONFIG)/methods
SRC_CONFIG_METHODS_EVT = $(SRC_CONFIG_METHODS)/Event

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_SERV_CTOR)/server_create.c \
	$(SRC_SERV_DTOR)/server_destroy.c \
	$(SRC_SERV_METHODS_NET)/accept_client.c \
	$(SRC_SERV_METHODS_NET)/handle_poll.c \
	$(SRC_SERV_METHODS_NET)/remove_client.c \
	$(SRC_SERV_METHODS_NET)/server_run.c \
	$(SRC_SERV_METHODS_NET)/setup_poll.c \
	$(SRC_SERV_METHODS_EVT)/on_client_connected.c \
	$(SRC_SERV_METHODS_EVT)/on_identify_client.c \
	$(SRC_SERV_METHODS_EVT)/on_event_not_found.c \
	$(SRC_SERV_METHODS_CMDS)/command_manager.c \
	$(SRC_SERV_METHODS_CMDS)/forward.c \
	$(SRC_SERV_METHODS_CMDS)/get_delay.c \
	$(SRC_SHARED)/shared.c \
	$(SRC_UTILS)/print_log.c \
	$(SRC_UTILS)/strip_linefeed.c \
	$(SRC_UTILS)/Queu/handle_queu.c \
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
	$(SRC_LIST_METHODS)/list_contain.c \
	$(SRC_CONFIG_CTOR)/config_create.c \
	$(SRC_CONFIG_DTOR)/config_destructor.c \
	$(SRC_CONFIG_METHODS)/help_message.c \
	$(SRC_CONFIG_METHODS)/is_float.c \
	$(SRC_CONFIG_METHODS)/is_int.c \
	$(SRC_CONFIG_METHODS)/parse_args.c \
	$(SRC_CONFIG_METHODS)/str_are_equals.c \
	$(SRC_CONFIG_METHODS_EVT)/frequency_arg.c \
	$(SRC_CONFIG_METHODS_EVT)/height_arg.c \
	$(SRC_CONFIG_METHODS_EVT)/help_arg.c \
	$(SRC_CONFIG_METHODS_EVT)/invalid_arg.c \
	$(SRC_CONFIG_METHODS_EVT)/port_arg.c \
	$(SRC_CONFIG_METHODS_EVT)/team_name_arg.c \
	$(SRC_CONFIG_METHODS_EVT)/team_size_arg.c \
	$(SRC_CONFIG_METHODS_EVT)/width_arg.c

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
