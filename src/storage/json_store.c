#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fs.h"
#include "json_store.h"

cJSON	*json_load(const char *path)
{
	cJSON	*root;
	char	*_buffer;

	_buffer = fs_read_file(path);
	if (NULL == _buffer)
		return (NULL);
	root = cJSON_Parse(_buffer);
	free(_buffer);
	return (root);
}

int		json_save(const char *path, cJSON *root)
{
	char	*_buffer;

	_buffer = cJSON_Print(root);
	if (NULL == _buffer)
		return (1);
	if (1 == fs_write_file(path, _buffer))
		return (free(_buffer), 1);
	free(_buffer);
	return (0);
}

cJSON	*find_command(const cJSON *commands, const char *alias)
{
	cJSON	*_cmd;
	cJSON	*_cmd_aliases;
	cJSON	*_alias;

	cJSON_ArrayForEach(_cmd, commands)
	{
		_cmd_aliases = cJSON_GetObjectItem(_cmd, "aliases");
		if (NULL == _cmd_aliases)
			continue;
		cJSON_ArrayForEach(_alias, _cmd_aliases)
		{
			if (0 == strcmp(_alias->valuestring, alias))
				return (_cmd);
		}
	}
	return (NULL);
}
