#include "main.h"

char	*load_file(const char *path)
{
	FILE	*_file;
	long	_size;
	long	_read;
	char	*buffer;

	_file = fopen(path, "r");
	if (NULL == _file)
		return (NULL);
	
	fseek(_file, 0, SEEK_END);
	_size = ftell(_file);
	rewind(_file);

	buffer = malloc(_size + 1);
	if (NULL == buffer)
		return (fclose(_file), NULL);
	
	_read = fread(buffer, 1, _size, _file);
	if (_size != _read)
		return (fclose(_file), free(buffer), NULL);
	buffer[_size] = '\0';
	fclose(_file);

	return (buffer);
}

cJSON	*load_protocole(void)
{
	char	*_json_content;
	cJSON	*_root;

	_json_content = load_file("src/protocole.json");
	if (NULL == _json_content)
	{
		printf("%s[ERROR]%s An error occured : LOAD JSON FAILED.\n", RED, WHITE);
		return (NULL);
	}

	_root = cJSON_Parse(_json_content);
	if (NULL == _root)
	{
		printf("%s[ERROR]%s An error occured : PARSE JSON FAILED.\n", RED, WHITE);
		free(_json_content);
		return (NULL);
	}

	free(_json_content);
	return (_root);
}

cJSON	*find_command(cJSON *commands, const char *name)
{
	cJSON	*_cmd;
	cJSON	*_command_aliases;
	cJSON	*_command_alias;

	cJSON_ArrayForEach(_cmd, commands)
	{
		_command_aliases = cJSON_GetObjectItem(_cmd, "names");
		if (NULL == _command_aliases)
			continue;
		cJSON_ArrayForEach(_command_alias, _command_aliases)
		{
			if (0 == strcmp(_command_alias->valuestring, name))
				return (_cmd);
		}
	}
	return (NULL);
}