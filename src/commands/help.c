#include <stdio.h>
#include <limits.h>
#include "json_store.h"
#include "log.h"
#include "core/paths.h"

# define RESET	"\033[0m"
# define BOLD	"\033[1m"
# define ITALIC	"\033[3m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define WHITE	"\033[37m"

/**
 * @brief Print a command with help format
 * @param cmd The JSON command
 * @return 1 if an error occured, else 0
 */
static int	print_command(const cJSON *cmd)
{
	cJSON	*_alias;
	cJSON	*_aliases;

	cJSON	*_description;
	cJSON	*_usage;
	int		_first;

	_aliases = cJSON_GetObjectItem(cmd, "aliases");
	_description = cJSON_GetObjectItem(cmd, "description");
	_usage = cJSON_GetObjectItem(cmd, "usage");
	if (NULL == _aliases || NULL == _description || NULL == _usage)
		return(log_error("parse JSON aliases, description or usage failed."), 1);

	_first = 1;
	printf("\n%s%s%s: %s\t[", BOLD, RED, cmd->string, RESET);

	cJSON_ArrayForEach(_alias, _aliases)
	{
		if (0 == _first)
			printf(", ");
		printf("%s", _alias->valuestring);
		_first = 0;
	}
	printf("]\n\n\t%s\n", _description->valuestring);
	printf("\n\t%s%sUsage:%s %s\n", ITALIC, GREEN, RESET, _usage->valuestring);
	return (0);
}

/**
 * @brief Display the help pannel
 * @param root The JSON root
 * @param command The command for specific help or NULL
 * @return 1 if an error occured, else 0
 */
static int display_pannel(const cJSON *root, const char *command)
{
	cJSON	*_commands;
	cJSON	*_cmd;

	_commands = cJSON_GetObjectItem(root, "commands");
	if (NULL == _commands)
		return (log_error("parse JSON commands."), 1);

	if (NULL == command)
	{
		printf("Here are all commands of %sgiteo-server%s, manager of your %shome git%s.\n\n", BLUE, WHITE, YELLOW, WHITE);
		cJSON_ArrayForEach(_cmd, _commands)
		{
			if (1 == print_command(_cmd))
				return (1);
		}
		return (0);
	}

	_cmd = find_command(_commands, command);
	if (NULL == _cmd)
		return (printf("%s[ERROR]%s Command not found.\nUse --help for more info.\n", RED, WHITE), 1);

	printf("Specific help for %s%s%s:\n\n", BLUE, command, WHITE);
	
	if (1 == print_command(_cmd))
			return (1);
	return (0);
}

int	main(int argc, const char **argv)
{
	(void)argc;

	cJSON	*_root;
	char	_path[PATH_MAX];

	giteo_settings_path("protocole.json", _path);
	_root = json_load(_path);
	if (NULL ==_root)
		return (1);
	if (1 == display_pannel(_root, argv[1]))
		return (cJSON_Delete(_root), 1);
	printf("\n%sgiteo-server manual, open source home git.%s\n", ITALIC, RESET);
	cJSON_Delete(_root);
	return (0);
}