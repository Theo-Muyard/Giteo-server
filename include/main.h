#ifndef GITEO_MAIN_H
# define GITEO_MAIN_H

// ======================================>
// =============== INCLUDES ==============
// ======================================>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <cJSON/cJSON.h>
# include <string.h>
# include <limits.h>

// ======================================>
// ================ COLORS ===============
// ======================================>

# define BLACK            "\033[30m"
# define RED            "\033[31m"
# define GREEN            "\033[32m"
# define YELLOW            "\033[33m"
# define BLUE            "\033[34m"
# define MAGENTA        "\033[35m"
# define CYAN            "\033[36m"
# define WHITE            "\033[37m"

// ======================================>
// ============== Formating ==============
// ======================================>

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

// ======================================>
// ============== FUNCTIONS ==============
// ======================================>

/**
 * @brief Handle the commands
 * @param command The command to execute
 * @param argv All arguments without the first and NULL terminated
 */
int		commands_handler(const char *command, char **argv);

#endif