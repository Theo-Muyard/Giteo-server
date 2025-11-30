#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

int		fs_file_exists(const char *path)
{
	FILE	*_file;

	_file = fopen(path, "r");
	if (NULL == _file)
		return (0);
	fclose(_file);
	return (1);
}

char	*fs_read_file(const char *path)
{
	FILE	*_file;
	char	*_buffer;
	size_t	_size;
	size_t	_read;

	_file = fopen(path, "r");
	if (NULL == _file)
		return (NULL);

	fseek(_file, 0, SEEK_END);
	_size = ftell(_file);
	rewind(_file);

	_buffer = malloc(_size + 1);
	if (NULL == _buffer)
		return (fclose(_file), NULL);
	
	_read = fread(_buffer, 1, _size, _file);
	if (_size != _read)
		return (fclose(_file), free(_buffer), NULL);
	_buffer[_size] = '\0';
	fclose(_file);

	return (_buffer);
}

int		fs_write_file(const char *path, const char *data)
{
	FILE	*_file;

	_file = fopen(path, "w");
	if (NULL == _file)
		return (1);
	if (0 > fprintf(_file, "%s", data))
		return (fclose(_file), 1);
	fclose(_file);
	return (0);
}
