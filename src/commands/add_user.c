#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "core/paths.h"
#include "log.h"
#include "fs.h"
#include "json_store.h"
#include "user_service.h"

#define SALT_LEN 16
#define HASH_LEN 64

static void	get_input(char *buffer, size_t size, char *prompt, int hide_input)
{
	struct termios oldt, newt;
	size_t	len;

	printf("%s", prompt);
	fflush(stdout);

	if (hide_input)
	{
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}

	if (fgets(buffer, size, stdin) == NULL)
		buffer[0] = '\0';

	len = strlen(buffer);

	if (len > 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = '\0';

	if (hide_input)
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

static void	to_hex(const unsigned char *input, size_t len, char *output)
{
	char	*_hexa;
	size_t	_i;

	_hexa = "0123456789abcdef";
	_i = 0;
	while (_i < len)
	{
		output[_i * 2] = _hexa[(input[_i] >> 4) & 0xF];
		output[_i * 2 + 1] = _hexa[input[_i] & 0xF];
		_i++;
	}
	output[len * 2] = '\0';
}

static int	hash_password(char *password, char *hex_password, char *hex_salt)
{
	unsigned char	_salt[SALT_LEN];
	unsigned char	_hash[HASH_LEN];

	if (0 == RAND_bytes(_salt, SALT_LEN))
		return (log_error("Internal error: RAND BYTES"), 1);

	if (0 == PKCS5_PBKDF2_HMAC(
		password, strlen(password),
		_salt, SALT_LEN,
		310000,
		EVP_sha512(),
		HASH_LEN,
		_hash
	))
		return (log_error("Internal error: PKCS5"), 1);

	to_hex(_hash, sizeof(_hash), hex_password);
	to_hex(_salt, sizeof(_salt), hex_salt);
	return (0);
}

static int	new_user(UserService *users, char *username, char *password, char *salt)
{
	time_t			_timestamp;
	char			_uuid[32];
	User			*_user;

	if (NULL == users || NULL == username || NULL == password || NULL == salt)
		return (1);

	_timestamp = time(NULL);
	sprintf(_uuid, "%ld", _timestamp);

	users->users = realloc(users->users, (users->count + 1) * sizeof(User));
	if (NULL == users->users)
		return (1);
	_user = &users->users[users->count];
	_user->_id = strdup(_uuid);
	_user->username = strdup(username);
	_user->password = strdup(password);
	_user->salt = strdup(salt);
	users->count++;
	return (0);
}

static int	is_valid_input(char *input)
{
	if (NULL == input || input[0] == '\0')
		return (0);

	while (*input)
	{
		if (!isspace((unsigned char)*input))
			return (1);
		++input;
	}
	return (0);
}

static int	is_valid_username(UserService *users, char *username)
{
	size_t	_i;

	if (!is_valid_input(username))
		return (0);

	_i = 0;
	while (_i < users->count)
	{
		if (NULL == users->users[_i].username)
		{
			_i++;
			continue;
		}
		if (0 == strcmp(users->users[_i].username, username))
			return (0);
		_i++;
	}
	return (1);
}

int	main(void)
{
	UserService	*_users;

	char			_username[256];
	char			_password[256];
	char			_hex_password[512];
	char			_hex_salt[512];

	char			_path[PATH_MAX];

	giteo_settings_path("users.json", _path);
	if (!fs_file_exists(_path))
		return (log_warning("Please setup the system before use this command."), 1);

	_users = user_service_load();
	if (NULL == _users)
		return (user_service_free(_users), log_error("Internal error: Load user service."), 1);

	get_input(_username, sizeof(_username), "Enter a username: ", 0);

	if (!is_valid_username(_users, _username))
		return (user_service_free(_users), log_error("Invalid username. Please try again."), 1);

	get_input(_password, sizeof(_password), "Enter a password: ", 1);
	printf("\n");

	if (!is_valid_input(_password))
		return (user_service_free(_users), log_error("Invalid password. Please try again."), 1);

	if (hash_password(_password, _hex_password, _hex_salt))
		return(user_service_free(_users), log_error("Internal error: password hashage."), 1);
	explicit_bzero(_password, sizeof(_password));

	if (new_user(_users, _username, _hex_password, _hex_salt))
		return(user_service_free(_users), log_error("Internal error: creating new user."), 1);
	
	user_service_save(_users);
	log_success("User added.");

	user_service_free(_users);
	return (0);
}
