##
## EPITECH PROJECT, 2025
## B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
## File description:
## Makefile
##

NAME_SERVER = zappy_server
NAME_GUI = zappy_gui
NAME_AI = zappy_ai

DIR_SERVER = server
DIR_GUI = gui
DIR_AI = ai

all: $(NAME_SERVER) $(NAME_GUI) $(NAME_AI)

$(NAME_SERVER):
	$(MAKE) -C $(DIR_SERVER)
	@mv $(DIR_SERVER)/$(NAME_SERVER) ./

$(NAME_AI):
	$(MAKE) -C $(DIR_AI)
	@mv $(DIR_AI)/bin/$(NAME_AI) ./

$(NAME_GUI): 	gui/CMakeLists.txt \
				$(shell find gui/src -name "*.cpp" -o -name "*.hpp")
	@mkdir -p $(DIR_GUI)/build
	@cd $(DIR_GUI)/build && cmake ..
	@cmake --build $(DIR_GUI)/build
	@cp $(DIR_GUI)/build/$(NAME_GUI) ./ 2>/dev/null || true




clean:
	$(MAKE) -C $(DIR_SERVER) clean
	$(MAKE) -C $(DIR_AI) clean
	@rm -rf $(DIR_GUI)/build

fclean: clean
	$(MAKE) -C $(DIR_SERVER) fclean
	$(MAKE) -C $(DIR_AI) fclean
	@rm -f $(NAME_SERVER) $(NAME_GUI) $(NAME_AI)

re: fclean all

.PHONY: all clean fclean re
