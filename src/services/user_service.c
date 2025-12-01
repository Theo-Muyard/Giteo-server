#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
	cJSON	*_id;
	cJSON	*_username;
	cJSON	*_password;
	cJSON	*_salt;

	_id = user_json;
	_username = cJSON_GetObjectItem(user_json, "username");
	_password = cJSON_GetObjectItem(user_json, "password");
	_salt = cJSON_GetObjectItem(user_json, "salt");

	if (NULL == _id || NULL == _username || NULL == _password || NULL == _salt)
		return (NULL);
	user = malloc(sizeof(User));
	if (NULL == user)
		return (NULL);
	user->_id = strdup(_id->string);
	user->username = strdup(_username->valuestring);
	user->password = strdup(_password->valuestring);
	user->salt = strdup(_salt->valuestring);
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
		return (NULL);
	users->count = _i;
	users->users = malloc((_i + 1) * sizeof(User));
	if (NULL == users->users)
		return (NULL);
	_i = 0;
	cJSON_ArrayForEach(_user_json, _root)
	{
		_user = get_user(_user_json);
		if (NULL == _user)
			return (NULL);
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
		cJSON_AddStringToObject(_user_json, "password", _user.password);
		cJSON_AddStringToObject(_user_json, "salt", _user.salt);

		cJSON_AddItemToObject(_root, _user._id, _user_json);
		_i++;
	}
	
	giteo_settings_path("users.json", _path);
	json_save(_path, _root);
	cJSON_Delete(_root);
	return (0);
}

int			user_service_add(UserService *svc, const char *username, const char *hash, const char *salt);

int			user_service_delete(UserService *svc, const char *username);

User		*user_service_find(UserService *svc, const char *username);

void		user_service_free(UserService *svc)
{
	size_t	_i;

	_i = 0;
	while (_i < svc->count)
	{
		free(svc->users[_i]._id);
		free(svc->users[_i].username);
		free(svc->users[_i].password);
		free(svc->users[_i].salt);
		++_i;
	}
	free(svc->users);
	free(svc);
}
