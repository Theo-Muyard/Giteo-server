#include "main.h"
#include "tools_json.h"
#include "tools_helper.h"

/**
 * @brief Execute a command by creating a new children processus
 * @param path The path of executable command
 * @param argv All arguments and NULL terminated
 */
static void	exec_command(const char *path, char **argv)
{
	pid_t	_pid;
	int		_state;
	char	*_final_path;
	char	_buff[PATH_MAX];

	_pid = fork();
	_state = 0;
	_final_path = get_real_path(path, _buff);

	if (-1 == _pid)
	{
		perror("fork");
		exit (1);
	}
	else if (0 == _pid)
	{
		execv(_final_path, argv);
		perror("execv");
		exit (1);
	}

	waitpid(_pid, &_state, 0);
}

int		commands_handler(const char *alias, char **argv)
{
	cJSON	*_root;
	cJSON	*_commands;
	cJSON	*_cmd;
	cJSON	*_command_file_exec;

	_root = load_protocole();
	_commands = cJSON_GetObjectItem(_root, "commands");
	if (NULL == _root || NULL == _commands)
			return (cJSON_Delete(_root), print_parse_error("root or commands"), 1);

	_cmd = find_command(_commands, alias);
	if (NULL == _cmd)
	{
		printf("%s[ERROR]%s Command not found.\nUse %sgiteo-server --help%s for more informations.\n", RED, WHITE, BLUE, WHITE);
		cJSON_Delete(_root);
		return (1);
	}

	_command_file_exec = cJSON_GetObjectItem(_cmd, "exec");
	if (NULL == _command_file_exec)
		return (cJSON_Delete(_root), print_parse_error("exec"), 1);

	exec_command(_command_file_exec->valuestring, argv + 1);
	cJSON_Delete(_root);
	return (1);
}
