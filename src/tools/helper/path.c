#include "main.h"

char	*get_real_path(const char *path, char *buffer)
{
	char	*_home_path;

	_home_path = getenv("HOME");
	if (NULL == _home_path)
		return (NULL);
	strncpy(buffer, _home_path, PATH_MAX - 1);
	strncat(buffer, "/.giteo-server/", PATH_MAX - strlen(buffer) - 1);
	strncat(buffer, path, PATH_MAX - strlen(buffer) - 1);
	return (buffer);
}