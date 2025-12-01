#include <stdio.h>
#include "commands_handler.h"
#include "log.h"

#define RED		"\033[31m"
#define BLUE	"\033[34m"
#define WHITE	"\033[37m"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		log_error("Missing arguments.\nUse %sgiteo-server --help%s for more informations.", BLUE, WHITE);
		return (1);
	}

	if (1 == commands_handler(argv[1], argv))
		return (1);
	return (0);
}