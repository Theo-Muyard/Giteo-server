#ifndef GITEO_USER_SERVICE_H
# define GITEO_USER_SERVICE_H

# include "stdio.h" 

typedef struct User
{
	char	*_id;
	char	*username;
	char	*password_hash;
	char	*salt;
} User;

typedef struct UserService
{
	User	*users;
	size_t	count;
} UserService;

/**
 * @brief Load the users JSON file.
 * @return The users and it's count.
 */
UserService	*user_service_load(void);

/**
 * @brief Save the userService in the JSON file.
 * @param svc The userService.
 * @return 0 for success or 1 if an error occured.
 */
int			user_service_save(UserService *svc);

/**
 * @brief Add a user to the userService.
 * @param svc The userService.
 * @param username The username of the new user.
 * @param password_hash The password hash of the new user.
 * @param salt The salt of the new user.
 * @return 0 for success or 1 if an error occured.
 */
int			user_service_add(UserService *svc, const char *username, const char *password_hash, const char *salt);

/**
 * @brief Delete a user to the userService.
 * @param svc The userService.
 * @param username The username of the user to delete it.
 * @return 0 for success or 1 if an error occured.
 */
int			user_service_delete(UserService *svc, const char *username);

/**
 * @brief Find a user in the userService.
 * @param svc The userService
 * @param username The username of the user to find it.
 * @return The User or NULL if an error occured.
 */
User		*user_service_find(UserService *svc, const char *username);

/**
 * @brief Free the userService correctly.
 * @param svc The userService.
 */
void		user_service_free(UserService *svc);

#endif