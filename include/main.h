#ifndef GITEO_MAIN_H
# define GITEO_MAIN_H

/*
==> INCLUDES
*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <cJSON/cJSON.h>
# include <string.h>

/*
==> COLORS
*/

# define BLACK            "\033[30m"
# define RED            "\033[31m"
# define GREEN            "\033[32m"
# define YELLOW            "\033[33m"
# define BLUE            "\033[34m"
# define MAGENTA        "\033[35m"
# define CYAN            "\033[36m"
# define WHITE            "\033[37m"

/*
==> FORMATTING
*/

# define RESET            "\033[0m"
# define BOLD            "\033[1m"
# define FAINT            "\033[2m"
# define ITALIC            "\033[3m"
# define UNDERLINE        "\033[4m"
# define BLINK            "\033[5m"
# define REVERSE        "\033[6m"
# define REVERSED        "\033[7m"
# define HIDDEN            "\033[8m"
# define STRIKETHROUGH    "\033[9m"

/*
==> Functions
*/

/**
 * @brief Load a file content
 * @param Path The path of the file
 * @return A string with all content of the file or NULL if an error was occured
 */
char	*load_file(const char *path);


int		commands_handler(char *path, char *command, char **argv);


void	exec_command(char *path, char **argv);

cJSON	*load_protocole(void);

cJSON	*find_command(cJSON *commands, const char *name);

#endif