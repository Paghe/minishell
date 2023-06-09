/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:36:41 by crepou            #+#    #+#             */
/*   Updated: 2023/06/08 19:59:26 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

void	input_redirection(t_redirection *red)
{
	int		fd;

	while (1)
	{
		if (fork() != 0)
			wait(NULL);
		else
		{
			fd = open(red->filename, O_RDONLY);
			dup2(fd, 0);
			execve(red->envp[0], red->args, red->envp);
			perror("error in child");
		}
		break ;
	}
	close(fd);
}
