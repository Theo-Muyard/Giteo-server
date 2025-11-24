.PHONY: all clean fclean re

# GLOBAL
NAME			=	giteo-server
BIN_FOLDER		=	bin
OBJ_FOLDER		=	obj

# COLORS
GREEN			=	\033[32m
RED				=	\033[31m
BLUE			=	\033[34m
WHITE			=	\033[37m
MAGENTA			=	\033[35m
YELLOW			=	\033[33m

# COMPILER
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -I./include -I./include/tools/json -I./include/tools/helper
LDFLAGS			=	-L./include/cJSON/build -lcjson

# export LD_LIBRARY_PATH=/home/tmuyard/Giteo/Giteo-server/include/cJSON/build:$LD_LIBRARY_PATH

# GITEO-SERVER SOURCE
SRC				=	src/main.c \
					src/tools/json/tools_json.c \
					src/tools/commands_handler.c \
					src/tools/helper/messages.c \
					# ...
SRC_OBJ			=	$(SRC:src/%.c=$(OBJ_FOLDER)/%.o)

# COMMANDS
SRC_COMMANDS	=	src/commands/setup.c \
					src/commands/help.c \
					# ...
COMMANDS		=	$(SRC_COMMANDS:src/commands/%.c=$(BIN_FOLDER)/commands/%)
COMMANDS_HELPER	=	src/tools/json/tools_json.c \
					src/tools/helper/messages.c \
					# ...

all: $(NAME) $(COMMANDS)
	@echo "$(BLUE)[00] $(WHITE)Compilation done."

$(NAME): $(SRC_OBJ)
	@mkdir -p $(BIN_FOLDER)
	@$(CC) $(CFLAGS) $(SRC_OBJ) $(LDFLAGS) -o $(BIN_FOLDER)/$(NAME)

$(OBJ_FOLDER)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_FOLDER)/commands/%: src/commands/%.c
	@mkdir -p $(BIN_FOLDER)/commands
	@$(CC) $(CFLAGS) $(COMMANDS_HELPER) $(LDFLAGS) $< -o $@

clean:
	@rm -rf $(OBJ_FOLDER)
	@echo "$(BLUE)[00] $(WHITE)Objects cleaned."

fclean: clean
	@rm -rf $(BIN_FOLDER)
	@echo "$(BLUE)[00] $(WHITE)Binary cleaned."

re: fclean all