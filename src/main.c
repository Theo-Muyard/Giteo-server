#include "main.h"
#include "cJSON/cJSON.h"

int	main(int argc, char **argv)
{
	pid_t	_pid;
	int		_state;
	char	*_json_file;

	if (argc == 1)
	{
		printf("%s[ERROR]%s Missing arguments.\nUse %sgiteo-server --help%s for more informations.\n", RED, WHITE, BLUE, WHITE);
		return (1);
	}

	_json_file = load_file("src/protocole.json");
	if (NULL == _json_file)
	{
		printf("%s[ERROR]%s An error was occured : LOAD JSON FAILED.\n", RED, WHITE);
		return (1);
	}

	printf("%s\n", _json_file);

	_pid = fork();
	_state = 0;

	if (-1 == _pid)
		return (perror("fork"), 1);
	else if (0 == _pid)
	{
		execl("./bin/commands/help", "help", NULL);
		perror("execl");
		exit (1);
	}
	else
	{
		printf("AU DEBUT\n");
		printf("ARG 1 : %s\n", argv[1]);

		waitpid(_pid, &_state, 0);

		if (WIFEXITED(_state))
		{
			printf("A LA FIN\n");
		}
	}
	return (0);
}