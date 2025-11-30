#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>

#include "fs.h"
#include "log.h"
#include "json_store.h"
#include "process.h"
#include "core/paths.h"

static int	create_file(char *path)
{
	FILE	*_file;

	_file = fopen(path, "r");

	if (NULL != _file)
	{
		fclose(_file);
		return (1);
	}

	_file = fopen(path, "w");
	if (NULL == _file)
		return (perror("fopen"), 1);
	fprintf(_file, "{}");
	
	fclose(_file);
	return (0);
}

int	main(void)
{
	// cJSON	*_root;
	char	_path[PATH_MAX];

	giteo_settings_path("users.json", _path);
	if (!fs_file_exists(_path))
		create_file(_path);

	giteo_settings_path("config.json", _path);
	if (fs_file_exists(_path))
		return (log_error("The system is already etablished."), 1);

	printf("Welcome on our setup system!\nNow, create your first user.\n\n");
	giteo_bin_path("/commands/adduser", _path);
	if (1 == process_exec(_path, (char **){NULL}))
	{
		printf("ERROR\n");
		return (1);
	}
	giteo_settings_path("config.json", _path);
	if (1 == create_file(_path))
	{
		printf("CREATE FILE ERROR \n");
		return (1);
	}
	log_success("The system has been created or updated successfully.");

	return (0);
}