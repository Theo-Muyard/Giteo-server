#ifndef GITEO_FS_H
# define GITEO_FS_H

/**
 * @brief Check if the file exists.
 * @param path The path of the file.
 * @return 1 if the file exists, 0 else.
 */
int		fs_file_exists(const char *path);

/**
 * @brief Read the content of the file.
 * @param path The path of the file.
 * @return A buffer with the content of the file, NULL if an error occured.
 */
char	*fs_read_file(const char *path);

/**
 * @brief Write data on the file.
 * @param path The path of the file.
 * @param data The data that will be written on the file.
 * @return 0 if the data was written correctly, 1 if an error occured.
 */
int		fs_write_file(const char *path, const char *data);

#endif