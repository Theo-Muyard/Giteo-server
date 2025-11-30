.PHONY: all clean fclean re

# GLOBAL
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I./include -I./include/core -I./include/services -I./include/storage

LDFLAGS				=	-L./include/cJSON/build -lcjson -Wl,-rpath,'$$ORIGIN/../libs'
LDFLAGS_COMMANDS	=	-L./include/cJSON/build -lcrypto -lcjson -Wl,-rpath,'$$ORIGIN/../../libs'

NAME				=	giteo-server

BIN_FOLDER			=	bin
OBJ_FOLDER			=	obj

# COLORS
GREEN				=	\033[32m
RED					=	\033[31m
BLUE				=	\033[34m
WHITE				=	\033[37m
MAGENTA				=	\033[35m
YELLOW				=	\033[33m

SRC					=	src/main.c \
						src/commands_handler.c \
						src/core/fs.c \
						src/core/log.c \
						src/core/paths.c \
						src/core/process.c \
						src/storage/json_store.c \
						# ...
SRC_OBJ				=	$(SRC:src/%.c=$(OBJ_FOLDER)/%.o)

SRC_COMMANDS		=	src/commands/help.c \
						src/commands/adduser.c \
						src/commands/setup.c \
						# ...
COMMANDS			=	$(SRC_COMMANDS:src/commands/%.c=$(BIN_FOLDER)/commands/%)
COMMANDS_HELPER		=	src/core/fs.c \
						src/core/log.c \
						src/core/paths.c \
						src/core/process.c \
						src/storage/json_store.c \
						# ...

all: $(NAME) $(COMMANDS)

$(NAME): $(SRC_OBJ)
	@mkdir -p $(BIN_FOLDER)
	@$(CC) $(CFLAGS) $(SRC_OBJ) -o $(BIN_FOLDER)/$(NAME) $(LDFLAGS)

$(OBJ_FOLDER)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_FOLDER)/commands/%: src/commands/%.c
	@mkdir -p $(BIN_FOLDER)/commands
	@$(CC) $(CFLAGS) $(COMMANDS_HELPER) $< -o $@ $(LDFLAGS_COMMANDS)

clean:
	@rm -rf $(OBJ_FOLDER)

fclean: clean
	@rm -rf $(BIN_FOLDER)

re: fclean all

dev:
	@sh uninstall.sh
	@sh install.sh

json:
	@echo "Building libs..."
	@cd include && \
	{ \
		git clone -q https://github.com/DaveGamble/cJSON.git >/dev/null 2>&1 || true; \
		cd cJSON; \
		mkdir -p build; \
		cd build; \
		cmake .. >/dev/null 2>&1; \
		make -s >/dev/null 2>&1; \
	}
	@echo "Libs done."