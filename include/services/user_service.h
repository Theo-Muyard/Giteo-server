#ifndef GITEO_USER_SERVICE_H
# define GITEO_USER_SERVICE_H

# include "stdio.h" 

typedef struct User
{
	char	*_id;
	char	*username;
	char	*password;
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
 * 
 */
int			user_service_save(UserService *svc);

/**
 * 
 */
int			user_service_add(UserService *svc, const char *username, const char *password, const char *salt);

/**
 * 
 */
int			user_service_delete(UserService *svc, const char *username);

/**
 * 
 */
User		*user_service_find(UserService *svc, const char *username);


/**
 * 
 */
void		user_service_free(UserService *svc);

/**
 * 
 */
// void	to_hex(const unsigned char *input, size_t len, char *output);

#endif