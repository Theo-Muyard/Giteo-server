#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "paths.h"

static int	giteo_folder_path(
	const char *folder,
	const char *filename,
	char *buffer
)
{
	char	_home[PATH_MAX];

	if (0 != giteo_home_path(_home))
		return (1);
	if (PATH_MAX <= snprintf(buffer, PATH_MAX, "%s%s%s", _home, folder, filename))
		return (1);
	return (0);
}

int	giteo_home_path(char *buffer)
{
	char	*_home;

	buffer[0] = '\0';
	_home = getenv("HOME");
	if (NULL == _home)
		return (1);
	snprintf(buffer, PATH_MAX, "%s/.giteo-server/", _home);
	return(0);
}

int	giteo_settings_path(const char *filename, char *buffer)
{
	return (giteo_folder_path("settings/", filename, buffer));
}


int	giteo_bin_path(const char *command, char *buffer)
{
	return (giteo_folder_path("bin/", command, buffer));
}
