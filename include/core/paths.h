#ifndef GITEO_PATHS_H
# define GITEO_PATHS_H

/**
 * @brief Get the path to the giteo-server. 
 * The path has been written to the buffer.
 * @param buffer A buffer with PATH_MAX size.
 * @return 0 for success or 1 if an error occured.
 */
int	giteo_home_path(char *buffer);

/**
 * @brief Get the path to the file in the settings folder located in the giteo-server folder.
 * The path has been written to the buffer.
 * @param buffer A buffer with PATH_MAX size.
 * @return 0 for success or 1 if an error occured.
 */
int	giteo_settings_path(const char *filename, char *buffer);

/**
 * @brief Get the path to the file in the bin folder located in the giteo-server folder.
 * The path has been written to the buffer.
 * @param buffer A buffer with PATH_MAX size.
 * @return 0 for success or 1 if an error occured.
 */
int	giteo_bin_path(const char *command, char *buffer);

#endif