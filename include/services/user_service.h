#ifndef GITEO_USER_SERVICE_H
# define GITEO_USER_SERVICE_H

# include "stdio.h" 

typedef struct User
{
	char	*username;
	char	*hash;
	char	*salt;
} User;

typedef struct UserService
{
	User	*users;
	size_t	count;
} UserService;

/**
 * 
 */
UserService	*user_service_load(void);

/**
 * 
 */
int			user_service_save(UserService *svc);

/**
 * 
 */
int			user_service_add(UserService *svc, const char *username, const char *hash, const char *salt);

/**
 * 
 */
int			user_service_delete(UserService *svc, const char *username);

/**
 * 
 */
User		*user_service_find(UserService *svc, const char *username);

#endif