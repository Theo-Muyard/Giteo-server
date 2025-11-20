#include "main.h"

int		commands_handler(char *path, char *command, char **argv)
{
	char	*_root;
	cJSON	*_parsed_root;

	cJSON	*_commands;
	cJSON	*_cmd;
	cJSON	*_item_name;
	cJSON	*_command_names;
	cJSON	*_command_exec_file;

	_root = load_file(path);
	if (NULL == _root)
	{
		printf("%s[ERROR]%s An error occured : LOAD JSON FAILED.\n", RED, WHITE);
		return (1);
	}

	_parsed_root = cJSON_Parse(_root);
	free(_root);
	_commands = cJSON_GetObjectItem(_parsed_root, "commands");
	if (NULL == _parsed_root || NULL == _commands)
	{
		printf("%s[ERROR]%s An error occured : PARSE JSON FAILED.\n", RED, WHITE);
		cJSON_Delete(_parsed_root);
		return (1);
	}

	cJSON_ArrayForEach(_cmd, _commands)
	{
		_command_names = cJSON_GetObjectItem(_cmd, "names");
		_command_exec_file = cJSON_GetObjectItem(_cmd, "exec");
		if (NULL == _command_names || NULL == _command_exec_file)
		{
			printf("%s[ERROR]%s An error occured : PARSE JSON FAILED.\n", RED, WHITE);
			cJSON_Delete(_parsed_root);
			return (1);
		}

		cJSON_ArrayForEach(_item_name, _command_names)
		{
			if (0 == strcmp(_item_name->valuestring, command))
			{
				exec_command(_command_exec_file->valuestring, argv + 1);
				cJSON_Delete(_parsed_root);
				return (0);
			}
		}
	}
	printf("%s[ERROR]%s Command not found.\nUse %sgiteo-server --help%s for more informations.\n", RED, WHITE, BLUE, WHITE);
	cJSON_Delete(_parsed_root);
	return (1);
}

void	exec_command(char *path, char **argv)
{
	pid_t	_pid;
	int		_state;

	_pid = fork();
	_state = 0;

	if (-1 == _pid)
	{
		perror("fork");
		exit (1);
	}
	else if (0 == _pid)
	{
		execv(path, argv);
		perror("execv");
		exit (1);
	}

	waitpid(_pid, &_state, 0);
}
