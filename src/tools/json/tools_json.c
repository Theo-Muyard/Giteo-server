#include "tools_json.h"
#include "tools_helper.h"

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
	char	*_file_path;
	char	_buff[PATH_MAX];
	char	*_json_content;
	cJSON	*_root;

	_file_path = get_real_path("settings/protocole.json", _buff);

	_json_content = load_file(_file_path);
	if (NULL == _json_content)
		return (printf("%s[ERROR]%s An error occured : LOAD JSON FAILED.\n", RED, WHITE), NULL);

	_root = cJSON_Parse(_json_content);
	if (NULL == _root)
		return (free(_json_content), print_parse_error("root"), NULL);

	free(_json_content);
	return (_root);
}

cJSON	*find_command(const cJSON *commands, const char *alias)
{
	cJSON	*_cmd;
	cJSON	*_command_aliases;
	cJSON	*_alias;

	cJSON_ArrayForEach(_cmd, commands)
	{
		_command_aliases = cJSON_GetObjectItem(_cmd, "aliases");
		if (NULL == _command_aliases)
			continue;
		cJSON_ArrayForEach(_alias, _command_aliases)
		{
			if (0 == strcmp(_alias->valuestring, alias))
				return (_cmd);
		}
	}
	return (NULL);
}
