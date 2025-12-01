#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "core/paths.h"
#include "log.h"
#include "fs.h"
#include "user_service.h"


int	main(int argc, char **argv)
{
	(void)argc;
	UserService	*_users;
	char		_path[PATH_MAX];
	
	giteo_settings_path("users.json", _path);
	if (!fs_file_exists(_path))
		return (log_warning("Please setup the system before use this command."), 1);

	if (!argv[1])
		return (log_error("Enter a username."), 1);
	_users = user_service_load();
	if (NULL == _users)
		return (user_service_free(_users), log_error("Internal error: Load user service."), 1);
	
	if (user_service_delete(_users, argv[1]))
		return (user_service_free(_users),log_error("User not found."), 1);
	user_service_save(_users);
	log_success("User removed.");
	user_service_free(_users);
	return (0);
}
