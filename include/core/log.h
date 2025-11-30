#ifndef GITEO_LOG_H
# define GITEO_LOG_H

/**
 * @brief Log on stderr an information message.
 * @param format The format of the message.
 * @param args The arguments of the message.
 */
void	log_info(const char *format, ...)
	__attribute__((__format__(__printf__, 1, 2)));

/**
 * @brief Log on stderr an warning message.
 * @param format The format of the message.
 * @param args The arguments of the message.
 */
void	log_warning(const char *format, ...)
	__attribute__((__format__(__printf__, 1, 2)));

/**
 * @brief Log on stderr an error message.
 * @param format The format of the message.
 * @param args The arguments of the message.
 */
void	log_error(const char *format, ...)
	__attribute__((__format__(__printf__, 1, 2)));

/**
 * @brief Log on stderr an success message.
 * @param format The format of the message.
 * @param args The arguments of the message.
 */
void	log_success(const char *format, ...)
	__attribute__((__format__(__printf__, 1, 2)));

#endif