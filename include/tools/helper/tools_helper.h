#ifndef GITEO_TOOLS_HELPER_H
# define GITEO_TOOLS_HELPER_H

// ======================================>
// =============== INCLUDES ==============
// ======================================>

# include <stdio.h>
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
 * @brief Print a parse error with an error message if needed
 * @param err The helper message
 */
void	print_parse_error(const char *err);

#endif