#ifndef GITEO_JSON_STORE_H
# define GITEO_JSON_STORE_H

#include "cJSON/cJSON.h"

/**
 * @brief Load a JSON file and parse it.
 * @param path The path of the JSON file.
 * @return A cJSON content of the file. Don't forget to delete it. or NULL if an error occured.
 */
cJSON	*json_load(const char *path);

/**
 * @brief Save a cJSON content. The content will be written on the file.
 * @param path The path of the JSON file.
 * @param root The cJSON content to write on the file.
 * @return 0 if success or 1 if an error occured.
 */
int		json_save(const char *path, cJSON *root);

/**
 * 
 */
cJSON	*find_command(const cJSON *commands, const char *alias);

#endif