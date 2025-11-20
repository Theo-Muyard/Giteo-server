#include "main.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("%s[ERROR]%s Missing arguments.\nUse %sgiteo-server --help%s for more informations.\n", RED, WHITE, BLUE, WHITE);
		return (1);
	}

	if (1 == commands_handler("src/protocole.json", argv[1], argv))
		return (1);
	return (0);
}