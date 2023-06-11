/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:36:41 by crepou            #+#    #+#             */
/*   Updated: 2023/06/11 21:40:54 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

void	output_redirection_renew(t_redirection *red)
{
	int	fd;

	while (1)
	{
		if (fork() != 0)
			wait(NULL);
		else
		{
			fd = open(red->filename, O_WRONLY | O_CREAT);
			dup2(fd, 1);
			execve(red->envp[0], red->args, red->envp);
			perror("error in child");
		}
		break ;
	}
	close(fd);
}

void	output_redirection_append(t_redirection *red)
{
	int	fd;

	while (1)
	{
		if (fork() != 0)
			wait(NULL);
		else
		{
			fd = open(red->filename, O_WRONLY | O_APPEND | O_CREAT);
			dup2(fd, 1);
			execve(red->envp[0], red->args, red->envp);
			perror("error in child");
		}
		break ;
	}
	close(fd);
}
