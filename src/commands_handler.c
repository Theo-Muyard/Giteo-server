#include <stdio.h>
#include <limits.h>

#include "process.h"
#include "log.h"
#include "core/paths.h"
#include "json_store.h"
#include "commands_handler.h"

# define BLUE	"\033[34m"
# define WHITE	"\033[37m"

int		commands_handler(const char *alias, char **argv)
{
	cJSON	*_root;
	cJSON	*_commands;
	cJSON	*_cmd;
	cJSON	*_cmd_exec_file;
	char	_path[PATH_MAX];

	giteo_settings_path("protocole.json", _path);
	_root = json_load(_path);
	if (NULL == _root)
		return (log_error("parse JSON failed."), 1);
	_commands = cJSON_GetObjectItem(_root, "commands");
	if (NULL == _commands)
		return (cJSON_Delete(_root), log_error("Missing 'commands' in JSON."), 1);
	
	_cmd = find_command(_commands, alias);
	if (NULL == _cmd)
	{	
		cJSON_Delete(_root);
		log_error("Command not found.\n , \
				Use %sgiteo-server --help%s for more informations.", BLUE, WHITE);
		return (1);
	}

	_cmd_exec_file = cJSON_GetObjectItem(_cmd, "exec");
	if (NULL == _cmd_exec_file)
		return (cJSON_Delete(_root), log_error("missing exec file."), 1);
	
	giteo_bin_path(_cmd_exec_file->valuestring, _path);
	process_exec(_path, argv + 1);
	cJSON_Delete(_root);
	return (0);
}
