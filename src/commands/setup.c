#include "main.h"
#include "tools_json.h"
#include "tools_helper.h"

#define SALT_LEN 16
#define HASH_LEN 64

static int	create_files(void)
{
	FILE	*_config_f;
	FILE	*_users_f;
	char	_buff[PATH_MAX];
	char	*_real_path;

	_real_path = get_real_path("settings/config.json", _buff);
	_config_f = fopen(_real_path, "r");

	_real_path = get_real_path("settings/users.json", _buff);
	_users_f = fopen(_real_path, "r");

	if (NULL != _config_f && NULL != _users_f)
		return (1);

	_users_f = fopen(_real_path, "w");
	fprintf(_users_f, "{}");
	_real_path = get_real_path("settings/config.json", _buff);
	_config_f = fopen(_real_path, "w");
	fprintf(_config_f, "{}");

	if (NULL == _config_f || NULL == _users_f)
	{
		perror("fopen");
		return (1);
	}

	fclose(_config_f);
	fclose(_users_f);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	// cJSON	*_root;

	if (1  == create_files())
	{
		printf("The system is already etablished.\n");
		return (1);
	}

	printf("The system has been created or updated successfully.\n");

	return (0);
}