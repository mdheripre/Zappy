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
DIR_AI = ia

all: $(NAME_SERVER) $(NAME_GUI) $(NAME_AI)

$(NAME_SERVER):
	$(MAKE) -C $(DIR_SERVER)
	@mv $(DIR_SERVER)/$(NAME_SERVER) ./

$(NAME_AI):
	$(MAKE) -C $(DIR_AI)
	@mv $(DIR_AI)/$(NAME_AI) ./

$(NAME_GUI):
	@echo "Building GUI using CMake..."
	@cmake -S $(DIR_GUI) -B $(DIR_GUI)/build > /dev/null
	@cmake --build $(DIR_GUI)/build > /dev/null
	@mv $(DIR_GUI)/build/$(NAME_GUI) ./ 2>/dev/null || true

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