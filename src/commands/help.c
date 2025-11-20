#include "main.h"

#define ASCII_TITLE \
" █████   █████          ████               ███████████                                           ████ \n" \
"▒▒███   ▒▒███          ▒▒███              ▒▒███▒▒▒▒▒███                                         ▒▒███ \n" \
" ▒███    ▒███   ██████  ▒███  ████████     ▒███    ▒███  ██████   ████████   ████████    ██████  ▒███ \n" \
" ▒███████████  ███▒▒███ ▒███ ▒▒███▒▒███    ▒██████████  ▒▒▒▒▒███ ▒▒███▒▒███ ▒▒███▒▒███  ███▒▒███ ▒███ \n" \
" ▒███▒▒▒▒▒███ ▒███████  ▒███  ▒███ ▒███    ▒███▒▒▒▒▒▒    ███████  ▒███ ▒███  ▒███ ▒███ ▒███████  ▒███ \n" \
" ▒███    ▒███ ▒███▒▒▒   ▒███  ▒███ ▒███    ▒███         ███▒▒███  ▒███ ▒███  ▒███ ▒███ ▒███▒▒▒   ▒███ \n" \
" █████   █████▒▒██████  █████ ▒███████     █████       ▒▒████████ ████ █████ ████ █████▒▒██████  █████\n" \
"▒▒▒▒▒   ▒▒▒▒▒  ▒▒▒▒▒▒  ▒▒▒▒▒  ▒███▒▒▒     ▒▒▒▒▒         ▒▒▒▒▒▒▒▒ ▒▒▒▒ ▒▒▒▒▒ ▒▒▒▒ ▒▒▒▒▒  ▒▒▒▒▒▒  ▒▒▒▒▒ \n" \
"                              ▒███                                                                    \n" \
"                              █████                                                                   \n" \
"                             ▒▒▒▒▒                                                                    \n" \

static int	print_command(cJSON *cmd)
{
	cJSON	*_n;
	cJSON	*_names;
	cJSON	*_description;
	cJSON	*_usage;
	int		_first;

	_names = cJSON_GetObjectItem(cmd, "names");
	_description = cJSON_GetObjectItem(cmd, "description");
	_usage = cJSON_GetObjectItem(cmd, "usage");

	if (NULL == _names || NULL == _description || NULL == _usage)
	{
		printf("%s[ERROR]%s An error occured : PARSE JSON FAILED.\n", RED, WHITE);
		return (1);
	}

	_first = 1;
	printf("\n%s%s%s: %s\t[", BOLD, RED, cmd->string, RESET);

	cJSON_ArrayForEach(_n, _names)
	{
		if (0 == _first)
			printf(", ");
		printf("%s", _n->valuestring);
		_first = 0;
	}
	printf("]\n");

	printf("\n\t%s\n", _description->valuestring);
	printf("\n\t%s%sUsage:%s %s\n", ITALIC, GREEN, RESET, _usage->valuestring);
	return (0);
}

static int full_pannel(cJSON *root)
{
	cJSON	*_commands;
	cJSON	*_cmd;

	_commands = cJSON_GetObjectItem(root, "commands");
	if (NULL == _commands)
	{
		printf("%s[ERROR]%s An error occured : PARSE JSON FAILED.\n", RED, WHITE);
		return (1);
	}

	printf("\n%s\n\n", ASCII_TITLE);

	printf("Here are all commands of %sgiteo-server%s, manager of your %shome git%s.\n\n", BLUE, WHITE, YELLOW, WHITE);
	cJSON_ArrayForEach(_cmd, _commands)
	{
		if (1 == print_command(_cmd))
			return (1);
	}
	printf("\n%sgiteo-server manual, open source home git.%s\n", ITALIC, RESET);
	return (0);
}

static int specific_pannel(cJSON *root, const char *command)
{
	cJSON	*_commands;
	cJSON	*_cmd;

	_commands = cJSON_GetObjectItem(root, "commands");
	if (NULL == _commands)
	{
		printf("%s[ERROR]%s An error occured : PARSE JSON FAILED.\n", RED, WHITE);
		return (1);
	}

	_cmd = find_command(_commands, command);
	if (NULL == _cmd)
	{
		printf("%s[ERROR]%s Command not found.\nUse --help for more info.\n", RED, WHITE);
		return (1);
	}
	printf("\n%s\n\n", ASCII_TITLE);
	printf("Specific help for %s%s%s:\n\n", BLUE, command, WHITE);
	
	if (1 == print_command(_cmd))
			return (1);
	printf("\n%sgiteo-server manual, open source home git.%s\n", ITALIC, RESET);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;

	cJSON	*_root;

	_root = load_protocole();
	if (NULL ==_root)
		return (1);
	if (NULL != argv[1])
	{
		if (1 == specific_pannel(_root, argv[1]))
		{
			cJSON_Delete(_root);
			return (1);
		}
	}
	else
	{
		if (1 == full_pannel(_root))
		{
			cJSON_Delete(_root);
			return (1);
		}
	}
	cJSON_Delete(_root);
	return (0);
}