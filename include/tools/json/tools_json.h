#ifndef GITEO_TOOLS_JSON_H
# define GITEO_TOOLS_JSON_H

// ======================================>
// =============== INCLUDES ==============
// ======================================>

# include <cJSON/cJSON.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// ======================================>
// ================ COLORS ===============
// ======================================>

# define RED            "\033[31m"
# define WHITE            "\033[37m"

// ======================================>
// ============== FUNCTIONS ==============
// ======================================>

/**
 * @brief Load a file content
 * @param Path The path of the file
 * @return A string with all content of the file or NULL if an error was occured
 */
char	*load_file(const char *path);

int		write_JSON_file(char *buffer, char *path);

/**
 * @brief Load and parse the JSON protocole file
 * @return The JSON parsed with cJSON or NULL if an error was occured
 */
cJSON	*load_protocole(void);

/**
 * @brief Find a command with it alias
 * @param commands The CJSON object with all commands
 * @param alias The alias of the command
 * @return The CJSON of the command or NULL if an error was occured
 */
cJSON	*find_command(const cJSON *commands, const char *alias);

#endif