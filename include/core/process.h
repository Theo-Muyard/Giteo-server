#ifndef GITEO_PROCESS_H
# define GITEO_PROCESS_H

/**
 * @brief Execute a binary as a child process
 * @param path The path of the binary program.
 * @param argv An array of arguments to pass to the binary.
 */
int	process_exec(const char *path, char **argv);

#endif