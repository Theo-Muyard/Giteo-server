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
	size_t		_i;

	char			_path[PATH_MAX];

	if (!argv[1])
		return (log_error("Enter a username."), 1);
	
	giteo_settings_path("users.json", _path);
	if (!fs_file_exists(_path))
		return (log_warning("Please setup the system before use this command."), 1);

	_users = user_service_load();
	if (NULL == _users)
		return (user_service_free(_users), log_error("Internal error: Load user service."), 1);
	
	_i = 0;
	while (_i < _users->count)
	{
		if (_users->users[_i].username)
		{
			if (strcmp(_users->users[_i].username, argv[1]) == 0)
			{
				free(_users->users[_i]._id);
				free(_users->users[_i].username);
				free(_users->users[_i].password);
				free(_users->users[_i].salt);
				_users->users[_i]._id = NULL;
				_users->users[_i].username = NULL;
				_users->users[_i].password = NULL;
				_users->users[_i].salt = NULL;
				user_service_save(_users);
				user_service_free(_users);
				return (log_success("User removed."), 0);
			}
		}
		_i++;
	}
	log_error("User not found.");
	user_service_free(_users);
	return (1);
}
