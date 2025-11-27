#include "main.h"
#include "tools_json.h"
#include "tools_helper.h"
#include <termios.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

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

int	main(void)
{
	char			_username[256];
	char			_password[256];

	unsigned char	_salt[SALT_LEN];
	unsigned char	_hash[HASH_LEN];

	char			_hex_password[512];

	char			*_buffer_content;
	char			_buff[PATH_MAX];
	char			*_real_path;
	
	char			*_out;

	cJSON			*_root;
	cJSON			*_new_user;

	_real_path = get_real_path("settings/users.json", _buff);
	_buffer_content = load_file(_real_path);

	_root = cJSON_Parse(_buffer_content);
	if (NULL == _root)
		return (print_parse_error("root"), 1);

	get_input(_username, sizeof(_username), "Enter a username: ", 0);
	get_input(_password, sizeof(_password), "Enter a password: ", 1);

	printf("\n\nUSERNAME: %s\n", _username);
	printf("PASSWORD: %s\n", _password);

	if (0 == RAND_bytes(_salt, SALT_LEN))
	{
		perror("RAND bytes");
		return (1);
	}

	if (0 == PKCS5_PBKDF2_HMAC(
		_password, strlen(_password),
		_salt, SALT_LEN,
		310000,
		EVP_sha512(),
		HASH_LEN,
		_hash
	))
	{
		perror("PKCS5");
		return (1);
	}

	to_hex(_hash, sizeof(_hash), _hex_password);
	explicit_bzero(_password, sizeof(_password));

	_new_user = cJSON_CreateObject();
	cJSON_AddStringToObject(_new_user, "username", _username);
	cJSON_AddStringToObject(_new_user, "password", _hex_password);
	cJSON_AddItemToObject(_root, "<user_id>", _new_user);

	_out = cJSON_Print(_root);

	write_JSON_file(_out, "/settings/users.json");

	cJSON_Delete(_root);
	free(_buffer_content);
	return (0);
}
