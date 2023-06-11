/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:49:01 by crepou            #+#    #+#             */
/*   Updated: 2023/06/11 21:53:49 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

/* 0: start, 1:middle, 2:end */
void	pipe_proccess(char *args[], int num, t_redirection *red)
{
	int	fd1;
	int	fd2;

	while (1)
	{
		if (fork() != 0)
			wait(NULL);
		else
		{
			if (num == 0)
			{
				fd1 = open("bus.txt", O_WRONLY | O_CREAT);
				dup2(fd1, 1);
				execve(red->envp[0], red->args, red->envp);
				perror("error in child");
			}
			else if (num == 1)
			{
				fd2 = open("bus.txt", O_RDONLY);
				dup2(fd2, 0);
				fd1 = open("bus.txt", O_WRONLY | O_CREAT);
				dup2(fd1, 1);
				execvpe(red->envp[0], red->args, red->envp);
				perror("error in child");
			}
			else
			{
				fd2 = open("bus.txt", O_RDONLY);
				dup2(fd2, 0);
				execvpe(red->envp[0], red->args, red->envp);
				perror("error in child");
			}
		}
		break ;
	}
	if (num == 0 || num == 1)
		close(fd1);
	if (num == 1 || num == 2)
		close(fd2);
}
