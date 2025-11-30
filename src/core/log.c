#include <stdio.h>
#include <stdarg.h>
#include "log.h"

#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"

static void	log_generic(
	const char *format,
	const char *prefix,
	const char *color,
	va_list args
)
{
	fprintf(stderr, "%s[%s]%s ", color, prefix, WHITE);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
}

void	log_info(const char *format, ...)
{
	va_list	_args;

	va_start(_args, format);
	log_generic(format, "Info", CYAN, _args);
	va_end(_args);
}

void	log_warning(const char *format, ...)
{
	va_list	_args;

	va_start(_args, format);
	log_generic(format, "Warning", YELLOW, _args);
	va_end(_args);
}

void	log_error(const char *format, ...)
{
	va_list	_args;

	va_start(_args, format);
	log_generic(format, "Error", RED, _args);
	va_end(_args);
}

void	log_success(const char *format, ...)
{
	va_list	_args;

	va_start(_args, format);
	log_generic(format, "Success", GREEN, _args);
	va_end(_args);
}
