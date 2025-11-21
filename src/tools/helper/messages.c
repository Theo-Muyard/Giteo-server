#include "tools_helper.h"

void	print_parse_error(const char *err)
{
	if (NULL == err)
	{
		printf("%s[ERROR]%s An error occured : PARSE JSON FAILED.\n", RED, WHITE);
		return ;
	}
	printf("%s[ERROR]%s An error occured : PARSE JSON FAILED (%s).\n", RED, WHITE, err);
}