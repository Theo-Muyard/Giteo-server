#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "core/paths.h"
#include "fs.h"
#include "json_store.h"
#include "user_service.h"

/**
 * 
 */
static User	*get_user(cJSON	*user_json)
{
	User	*user;
	cJSON	*_username;
	cJSON	*_password_hash;
	cJSON	*_salt;

	_username = cJSON_GetObjectItem(user_json, "username");
	_password_hash = cJSON_GetObjectItem(user_json, "password_hash");
	_salt = cJSON_GetObjectItem(user_json, "salt");

	if (NULL == _username || NULL == _password_hash || NULL == _salt)
		return (NULL);
	user = malloc(sizeof(User));
	if (NULL == user)
		return (NULL);
	user->_id = strdup(user_json->string);
	user->username = strdup(_username->valuestring);
	user->password_hash = strdup(_password_hash->valuestring);
	user->salt = strdup(_salt->valuestring);
	if (NULL == user->_id || NULL == user->username || NULL == user->password_hash || NULL == user->salt)
		return (NULL);
	return (user);
}

UserService	*user_service_load(void)
{
	UserService	*users;
	User		*_user;
	cJSON		*_root;
	cJSON		*_user_json;
	size_t		_i;
	char		_path[PATH_MAX];

	giteo_settings_path("users.json", _path);
	_root = json_load(_path);
	if (NULL == _root)
		return (NULL);

	_i = 0;
	cJSON_ArrayForEach(_user_json, _root)
		++_i;
	users = malloc(sizeof(UserService));
	if (NULL == users)
		return (cJSON_Delete(_root), NULL);
	users->count = _i;
	users->users = malloc(_i * sizeof(User));
	if (NULL == users->users)
		return (cJSON_Delete(_root), free(users), NULL);
	_i = 0;
	cJSON_ArrayForEach(_user_json, _root)
	{
		_user = get_user(_user_json);
		if (NULL == _user)
			return (cJSON_Delete(_root), user_service_free(users), NULL);
		users->users[_i] = *_user;
		free(_user);
		++_i;
	}
	cJSON_Delete(_root);
	return (users);
}

int			user_service_save(UserService *svc)
{
	cJSON	*_root;
	cJSON	*_user_json;
	User	_user;
	size_t	_i;
	char	_path[PATH_MAX];

	if (NULL == svc)
		return (1);
	
	_root = cJSON_CreateObject();
	if (NULL == _root)
		return (1);

	_i = 0;
	while (_i < svc->count)
	{
		_user_json = cJSON_CreateObject();
		if (NULL == _user_json)
			return (cJSON_Delete(_root), 1);
		_user = svc->users[_i];
		cJSON_AddStringToObject(_user_json, "username", _user.username);
		cJSON_AddStringToObject(_user_json, "password_hash", _user.password_hash);
		cJSON_AddStringToObject(_user_json, "salt", _user.salt);

		cJSON_AddItemToObject(_root, _user._id, _user_json);
		_i++;
	}
	
	giteo_settings_path("users.json", _path);
	json_save(_path, _root);
	cJSON_Delete(_root);
	return (0);
}

int			user_service_add(UserService *svc, const char *username, const char *password_hash, const char *salt)
{
	time_t			_timestamp;
	char			_uuid[32];
	User			*_user;
	User			*_tmp;

	if (NULL == svc || NULL == username || NULL == password_hash || NULL == salt)
		return (1);

	_timestamp = time(NULL);
	sprintf(_uuid, "%ld", _timestamp);

	_tmp = realloc(svc->users, (svc->count + 1) * sizeof(User));
	if (NULL == _tmp)
		return (1);
	svc->users = _tmp;
	_user = &svc->users[svc->count];
	_user->_id = strdup(_uuid);
	_user->username = strdup(username);
	_user->password_hash = strdup(password_hash);
	_user->salt = strdup(salt);
	if (NULL == _user->_id || NULL == _user->username || NULL == _user->password_hash || NULL == _user->salt)
		return (1);
	svc->count++;
	return (0);
}

int			user_service_delete(UserService *svc, const char *username)
{
	User	*_user;
	size_t	_i;
	User	*_tmp;

	_user = user_service_find(svc, username);
	if (NULL == _user)
		return (1);

	free(_user->_id);
	free(_user->username);
	free(_user->password_hash);
	free(_user->salt);

	_i = _user - svc->users;
	memmove(&svc->users[_i], &svc->users[_i+1], (svc->count - _i - 1) * sizeof(User));
	svc->count--;
	_tmp = realloc(svc->users, svc->count * sizeof(User));
	if (NULL == _tmp)
		return (1);
	svc->users = _tmp;
	return (0);
}

User		*user_service_find(UserService *svc, const char *username)
{
	size_t	_i;

	_i = 0;
	while (_i < svc->count)
	{
		if (svc->users[_i].username)
		{
			if (strcmp(svc->users[_i].username, username) == 0)
				return (&svc->users[_i]);
		}
		_i++;
	}
	return (NULL);
}

void		user_service_free(UserService *svc)
{
	size_t	_i;

	_i = 0;
	while (_i < svc->count)
	{
		free(svc->users[_i]._id);
		free(svc->users[_i].username);
		free(svc->users[_i].password_hash);
		free(svc->users[_i].salt);
		++_i;
	}
	free(svc->users);
	free(svc);
}
