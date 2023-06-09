/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:49:01 by crepou            #+#    #+#             */
/*   Updated: 2023/06/22 10:06:40 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

int	init_pipes(t_cmds **cmds, int index)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	cmds[index]->data.pipe_out = pipe_fd[WRITE_END];
	if (cmds[index + 1])
		cmds[index + 1]->data.pipe_in = pipe_fd[READ_END];
	return (0);
}

void	close_all(t_cmds **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->data.pipe_in != -1)
			close(cmds[i]->data.pipe_in);
		if (cmds[i]->data.pipe_out != -1)
			close(cmds[i]->data.pipe_out);
		if (cmds[i]->data.fd_in != -1)
			printf("fd in: %i\n", cmds[i]->data.fd_in);
		if (cmds[i]->data.fd_out != -1)
			printf("fd out: %i\n", cmds[i]->data.fd_out);
		i++;
	}
}

/* 0: start, 1:middle, 2:end */
void	pipe_proccess(t_cmds **red, char **envp, t_cmds **all , int n_commands)
{
	int	pid;

	(void)all;
	if (if_is_builtin((*red)->cmds[0]) && n_commands ==  1)
	{
		built_in(*red, envp);
		if ((*red)->data.pipe_in != -1)
			close((*red)->data.pipe_in);
		if ((*red)->data.pipe_out != -1)
			close((*red)->data.pipe_out);
		return ;
	}
	// if ((*red)->data.pipe_in != -1)
	// 	dup2((*red)->data.pipe_in, READ_END);
	// if ((*red)->data.pipe_out != -1)
	// 	dup2((*red)->data.pipe_out, WRITE_END);
	pid = fork();
	if (pid == -1)
	{
		perror("pipe_process\n");
		return ;
	}
	if (pid == 0)
	{
		if (if_is_builtin((*red)->cmds[0]))
		{
			built_in(*red, envp);
			exit(0);
		}
		else
		{
			if ((*red)->data.pipe_in != -1)
				dup2((*red)->data.pipe_in, READ_END);
			if ((*red)->data.pipe_out != -1)
				dup2((*red)->data.pipe_out, WRITE_END);
			close_all(all);
			if ((*red)->data.input || (*red)->data.output)
			{
				(*red)->data.fd_in = open((*red)->data.input, O_RDONLY);
				// if ((*red)->data.is_append)
					// (*red)->data.fd_out = open((*red)->data.output, O_WRONLY | O_APPEND | O_CREAT, 0644);
				// else
					(*red)->data.fd_out = open((*red)->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				redirect_io((*red)->data.fd_in, (*red)->data.fd_out);
				close((*red)->data.fd_in);
				close((*red)->data.fd_out);
			}
			//while(1);
			(*red)->cmds = escape_quotes_cmds((*red)->cmds);
			if (ft_strncmp((*red)->cmds[0], "./", 2) == 0)
			{
				if (execve((*red)->cmds[0], (*red)->cmds, envp) == -1)
					exit(-1);
			}
			else
			{
				if (execve((char const *)(*red)->data.env, (*red)->cmds, envp) == -1)
					exit(-1);
			}
		}
		
	}
		if ((*red)->data.pipe_in != -1)
			close((*red)->data.pipe_in);
		if ((*red)->data.pipe_out != -1)
			close((*red)->data.pipe_out);
	////close_all()
	//printf("waiting for %s %i\n",(char const *)(*red)->data.env,pid);
	waitpid(pid, NULL, 0);
	//printf("stop waiting\n");
}
