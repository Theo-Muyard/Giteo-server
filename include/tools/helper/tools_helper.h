#ifndef GITEO_TOOLS_HELPER_H
# define GITEO_TOOLS_HELPER_H

// ======================================>
// =============== INCLUDES ==============
// ======================================>

# include <stdio.h>
# include <string.h>
# include <limits.h>

// ======================================>
// ================ COLORS ===============
// ======================================>

# define RED	"\033[31m"
# define WHITE	"\033[37m"

// ======================================>
// ============== FUNCTIONS ==============
// ======================================>

/**
 * @brief Print a parse error with an error message if needed
 * @param err The helper message
 */
void	print_parse_error(const char *err);

/**
 * @brief Get the real path of a file
 * @param path The relative path of the file
 * @param buffer The buffer 
 * @return The real path of the file or NULL if an error occured
 */
char	*get_real_path(const char *path, char *buffer);

#endif