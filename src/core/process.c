#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "process.h"

int	process_exec(const char *path, char **argv)
{
	pid_t	_pid;
	int		_state;

	// printf("PATH: %s\n", path);
	_pid = fork();
	_state = 0;
	if (-1 == _pid)
	{
		perror("fork");
		exit (1);
	}
	else if (0 == _pid)
	{
		execv(path, argv);
		perror("execv");
		exit (1);
	}

	waitpid(_pid, &_state, 0);

	if (WIFEXITED(_state))
		return (WEXITSTATUS(_state));
	return (0);
}
