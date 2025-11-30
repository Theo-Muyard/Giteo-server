#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "core/paths.h"
#include "log.h"
#include "fs.h"
#include "process.h"
#include "json_store.h"

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

static int	add_to_json_file(cJSON *root, char *username, char *hex_pasword, char *hex_salt)
{
	cJSON			*_new_user;
	time_t			_timestamp;
	char			_uuid[32];
	char			_path[PATH_MAX];

	giteo_settings_path("users.json", _path);
	_timestamp = time(NULL);
	sprintf(_uuid, "%ld", _timestamp);
	_new_user = cJSON_CreateObject();
	cJSON_AddStringToObject(_new_user, "username", username);
	cJSON_AddStringToObject(_new_user, "password", hex_pasword);
	cJSON_AddStringToObject(_new_user, "salt", hex_salt);
	cJSON_AddItemToObject(root, _uuid, _new_user);

	json_save(_path, root);
	return (0);
}

static int	check_valid_input(char *input)
{
	if (NULL == input || input[0] == '\0')
		return (1);

	while (*input)
	{
		if (!isspace((unsigned char)*input))
			return (0);
		++input;
	}
	return (1);
}

static int	check_valid_username(cJSON *root, char *username)
{
	cJSON			*_user;

	if (check_valid_input(username))
		return (1);

	cJSON_ArrayForEach(_user, root)
	{
		if (0 == strcmp(username, cJSON_GetObjectItem(_user, "username")->valuestring))
			return (1);
	}
	return (0);
}

int	main(void)
{
	char			_username[256];
	char			_password[256];
	char			_hex_password[512];
	char			_hex_salt[512];

	char			*_buffer_content;
	char			_real_path[PATH_MAX];
	
	cJSON			*_root;

	giteo_settings_path("users.json", _real_path);

	_buffer_content = fs_read_file(_real_path);
	if (NULL == _buffer_content)
		return (log_warning("Please setup the system before use this command."), 1);

	_root = cJSON_Parse(_buffer_content);
	if (NULL == _root)
		return (log_error("JSON parse failed."), 1);

	get_input(_username, sizeof(_username), "Enter a username: ", 0);

	if (check_valid_username(_root, _username))
		return (log_error("Invalid username. Please try again."), 1);

	get_input(_password, sizeof(_password), "Enter a password: ", 1);
	printf("\n");

	if (check_valid_input(_password))
		return (log_error("Invalid password. Please try again."), 1);

	if (1 == hash_password(_password, _hex_password, _hex_salt))
		return(log_error("Internal error: password hashage."), 1);

	add_to_json_file(_root, _username, _hex_password, _hex_salt);
	log_success("User added.");

	explicit_bzero(_password, sizeof(_password));
	cJSON_Delete(_root);
	free(_buffer_content);
	return (0);
}
