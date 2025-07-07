#SILENCE THE ENTERING/LEAVING DIRECTORY MESSAGE
MAKEFLAGS += --no-print-directory

#DEFINE COLOR AND STYLE CODES
RESET = \033[0m
BOLD = \033[1m
ITALIC = \033[3m
UNDERLINE = \033[4m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m

#COMPILER AND FLAGS
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

#SOURCE FILES
SRC =	./src/main.c ./src/parsing.c ./src/utils.c ./src/errors.c \
		./src/init.c

#DIRECTORIES
OBJ_DIR = obj

#DEFINE OBJECTS
OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

#PROGRAM NAME
NAME = philo

#DEFAULT TARGET
all: $(NAME)
	@echo "${BOLD}${GREEN}Philo built ✅${RESET}"

#LINKING EXECUTABLE !!!FLAGS
$(NAME): $(OBJ_DIR) $(OBJ)
	@${CC} ${CFLAGS} $(OBJ) -o $(NAME)
	@echo "${ITALIC}Building Philo...🔨${RESET}"

#BUILD LIBRARIES
#none

#CREATING OBJECT DIRECTORIES
$(OBJ_DIR):
	@mkdir -p $@

#COMPILING .c FILES INTO .o FILES (INSIDE OBJ DIR) !!!FLAGS
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@${CC} ${CFLAGS} -c $< -o $@

#BASIC RULES
clean:
	@rm -rf $(OBJ_DIR)
	@echo "${ITALIC}Cleaning object files...🍃${RESET}"
	@echo "${GREEN}${BOLD}Done !${RESET}"

fclean: clean
	@rm -rf $(NAME)
	@echo "${ITALIC}Cleaning everything...🍃${RESET}"
	@echo "${GREEN}${BOLD}Done !${RESET}"

re: fclean all

.PHONY: all clean fclean re
