##
## EPITECH PROJECT, 2025
## B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
## File description:
## Makefile
##

NAME = zappy_server

SRC_DIR = src
SRC_PLAYER = $(SRC_DIR)/Player
SRC_PLAYER_CTOR = $(SRC_PLAYER)/constructor
SRC_PLAYER_DTOR = $(SRC_PLAYER)/destructor
SRC_PLAYER_METHODS = $(SRC_PLAYER)/methods
SRC_SERVER = $(SRC_DIR)/Server
SRC_SERV_CTOR = $(SRC_SERVER)/constructor
SRC_SERV_DTOR = $(SRC_SERVER)/destructor
SRC_SERV_METHODS = $(SRC_SERVER)/methods
SRC_SERV_EVENT = $(SRC_SERVER)/events
SRC_CMD_MANAGER = $(SRC_DIR)/Command_Manager
SRC_CMD_MANAGER_CTOR = $(SRC_CMD_MANAGER)/constructor
SRC_CMD_MANAGER_DTOR = $(SRC_CMD_MANAGER)/destructor
SRC_CMD_MANAGER_PARSER = $(SRC_CMD_MANAGER)/Parser
SRC_CMD_MANAGER_PARSER_HELPERS = $(SRC_CMD_MANAGER_PARSER)/Helper
SRC_CMD_MANAGER_METHODS = $(SRC_CMD_MANAGER)/methods
SRC_CMD_MANAGER_EVENTS = $(SRC_CMD_MANAGER)/events
SRC_CMD_MANAGER_EVENTS_IA = $(SRC_CMD_MANAGER_EVENTS)/ia
SRC_CMD_MANAGER_EVENTS_HANDLER = $(SRC_CMD_MANAGER_EVENTS_IA)/handler
SRC_CMD_MANAGER_EVENTS_RESPONSE = $(SRC_CMD_MANAGER_EVENTS_IA)/response
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
SRC_CONFIG = $(SRC_DIR)/Config
SRC_CONFIG_CTOR = $(SRC_CONFIG)/constructor
SRC_CONFIG_DTOR = $(SRC_CONFIG)/destructor
SRC_CONFIG_METHODS = $(SRC_CONFIG)/methods
SRC_CONFIG_METHODS_EVT = $(SRC_CONFIG)/Event
SRC_GAME = $(SRC_DIR)/Game
SRC_GAME_CTOR = $(SRC_GAME)/constructor
SRC_GAME_DTOR = $(SRC_GAME)/destructor
SRC_GAME_METHODS = $(SRC_GAME)/methods
SRC_GAME_EVENT = $(SRC_GAME)/event
SRC_POLL_MANAGER = $(SRC_DIR)/Poll_manager
SRC_POLL_MANAGER_CTOR = $(SRC_POLL_MANAGER)/constructor
SRC_POLL_MANAGER_DTOR = $(SRC_POLL_MANAGER)/destructor
SRC_POLL_MANAGER_METHODS = $(SRC_POLL_MANAGER)/methods

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
	$(SRC_SERV_METHODS)/get_next_tick.c \
	$(SRC_SERV_METHODS)/get_delay.c \
	$(SRC_SERV_METHODS)/handle_poll.c \
	$(SRC_SERV_METHODS)/remove_client.c \
	$(SRC_SERV_METHODS)/server_run.c \
	$(SRC_SERV_METHODS)/setup_poll.c \
	$(SRC_SERV_METHODS)/reject_client.c \
	$(SRC_CMD_MANAGER_CTOR)/command_manager_create.c \
	$(SRC_CMD_MANAGER_DTOR)/command_manager_destroy.c \
	$(SRC_CMD_MANAGER_METHODS)/command_manager_identify.c \
	$(SRC_CMD_MANAGER_METHODS)/command_manager_process_all.c \
	$(SRC_CMD_MANAGER_METHODS)/command_manager_register_all.c \
	$(SRC_CMD_MANAGER_METHODS)/command_manager_process_response.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/forward.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/left.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/right.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/look.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/inventory.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/take.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/drop.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/eject.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/fork.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/broadcast.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/connect_nbr.c \
	$(SRC_CMD_MANAGER_EVENTS_HANDLER)/incantation.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_moved_player.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_player_died.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_connect_player.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_look.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_inventory.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_eject.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_drop.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_broadcast.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_egg_laid.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_start_incantation.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_tile_updated.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_end_incantation.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_take.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_player_eat.c \
	$(SRC_CMD_MANAGER_EVENTS_RESPONSE)/response_egg_die.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/bct.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/msz.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pex.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pbc.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pdi.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/edi.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pic.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pie.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/seg.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pdr.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pgt.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/enw.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/sgt.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/tna.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/smg.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/ebo.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pfk.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/mct.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/sbp.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pnw.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/ppo.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/plv.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/pin.c \
	$(SRC_CMD_MANAGER_EVENTS_GUI)/sst.c \
	$(SRC_CMD_MANAGER_PARSER)/get_player_number.c \
	$(SRC_CMD_MANAGER_PARSER_HELPERS)/is_num.c \
	$(SRC_CMD_MANAGER_EVENTS)/not_found.c \
	$(SRC_SHARED)/shared.c \
	$(SRC_UTILS_LOG)/print_log.c \
	$(SRC_UTILS_HELPERS)/time.c \
	$(SRC_UTILS_HELPERS)/strip_linefeed.c \
	$(SRC_UTILS_HELPERS)/find_player_by_id.c \
	$(SRC_UTILS_HELPERS)/parsing_command.c \
	$(SRC_UTILS_HELPERS)/event_type_name.c \
	$(SRC_UTILS_HELPERS)/find_team.c \
	$(SRC_UTILS_QUEUE)/handle_queue.c \
	$(SRC_DISP_CTOR)/dispatcher_create.c \
	$(SRC_DISP_DTOR)/dispatcher_destroy.c \
	$(SRC_DISP_METHODS)/dispatcher_emit.c \
	$(SRC_DISP_METHODS)/dispatcher_register.c \
	$(SRC_LIST_CTOR)/list_create.c \
	$(SRC_LIST_DTOR)/list_destroy.c \
	$(SRC_LIST_METHODS)/list_clear.c \
	$(SRC_LIST_METHODS)/list_pop_front.c \
	$(SRC_LIST_METHODS)/list_push_front.c \
	$(SRC_LIST_METHODS)/list_consume.c \
	$(SRC_LIST_METHODS)/list_push_back.c \
	$(SRC_LIST_METHODS)/list_size.c \
	$(SRC_LIST_METHODS)/list_remove.c \
	$(SRC_LIST_METHODS)/list_front.c \
	$(SRC_LIST_METHODS)/list_contain.c \
	$(SRC_LIST_METHODS)/list_index.c \
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
	$(SRC_CONFIG_METHODS_EVT)/width_arg.c \
	$(SRC_GAME_CTOR)/game_create.c \
	$(SRC_GAME_DTOR)/game_destroy.c \
	$(SRC_GAME_METHODS)/dispatch_game_event.c \
	$(SRC_GAME_METHODS)/count_team_members.c \
	$(SRC_GAME_METHODS)/update_players.c \
	$(SRC_GAME_METHODS)/has_finished.c \
	$(SRC_GAME_METHODS)/spawn_ressources.c \
	$(SRC_GAME_METHODS)/get_winner.c \
	$(SRC_GAME_METHODS)/game_update.c \
	$(SRC_GAME_METHODS)/get_player_on_tile.c \
	$(SRC_GAME_METHODS)/game_update_incantation.c \
	$(SRC_GAME_METHODS)/check_incantate.c \
	$(SRC_GAME_EVENT)/player_moved.c \
	$(SRC_GAME_EVENT)/player_died.c \
	$(SRC_GAME_EVENT)/number_player.c \
	$(SRC_GAME_EVENT)/look_around.c \
	$(SRC_GAME_EVENT)/drop.c \
	$(SRC_GAME_EVENT)/eject.c \
	$(SRC_GAME_EVENT)/take.c \
	$(SRC_GAME_EVENT)/start_incantation.c \
	$(SRC_GAME_EVENT)/end_incantation.c \
	$(SRC_GAME_EVENT)/broadcast.c \
	$(SRC_GAME_EVENT)/inventory.c \
	$(SRC_GAME_EVENT)/egg_laid.c \
	$(SRC_PLAYER_CTOR)/player_create.c \
	$(SRC_PLAYER_DTOR)/player_destroy.c \
	$(SRC_PLAYER_METHODS)/add_ressource.c \
	$(SRC_PLAYER_METHODS)/remove_ressource.c \
	$(SRC_PLAYER_METHODS)/move.c \
	$(SRC_PLAYER_METHODS)/die.c \
	$(SRC_PLAYER_METHODS)/update.c \
	$(SRC_POLL_MANAGER_CTOR)/poll_manager_create.c \
	$(SRC_POLL_MANAGER_DTOR)/poll_manager_destroy.c \
	$(SRC_POLL_MANAGER_METHODS)/resize.c \
	$(SRC_POLL_MANAGER_METHODS)/get_fds.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Iinclude -g -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -Iinclude

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
