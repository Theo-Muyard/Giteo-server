#include "main.h"

char	*load_file(const char *path)
{
	FILE	*_file;
	long	_size;
	char	*buffer;

	_file = fopen(path, "r");
	if (NULL == _file)
		return (NULL);
	
	fseek(_file, 0, SEEK_END);
	_size = ftell(_file);
	rewind(_file);

	buffer = malloc(_size + 1);
	if (NULL == buffer)
		return (NULL);
	
	fread(buffer, 1, _size, _file);
	buffer[_size] = '\0';
	fclose(_file);

	return (buffer);
}