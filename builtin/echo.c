/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:27:24 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/22 14:21:35 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/lexer.h"

int	is_echo_newline(char *current)
{
	int	i;

	i = 0;
	while (current[i + 2] == 'n')
	{
		i++;
		if (current[i + 2] == '\0')
			return (0);
		else if (current[i + 2] != 'n')
			return (1);
	}
	return (0);
}

void	echo_newline(t_cmds **cmds)
{
	int		no_newline;
	int		i;


	no_newline = 0;
	i = 0;
	while (cmds[0]->cmds[0][i])
	{
		cmds[0]->cmds[0][i]= ft_tolower(cmds[0]->cmds[0][i]);
		i++;
	}
	i = 0;
	if (!ft_strncmp(cmds[0]->cmds[i], "echo", 5) && !cmds[0]->cmds[i + 1])
	{
		if (cmds[0]->data.pipe_out != -1)
			ft_putstr_fd("\n", cmds[0]->data.pipe_out);
		else
			ft_putstr_fd("\n", 1);
		return ;
	}
	if (!ft_strncmp(cmds[0]->cmds[i], "echo", 5))
	{
		if (cmds[0]->cmds[i + 1])
			i++;
		while (cmds[0]->cmds[i] && cmds[0]->cmds[i][0] != '\"' && cmds[0]->cmds[i][0] != '\'' && !ft_memcmp(cmds[0]->cmds[i], "-n", 2))
		{
			no_quote(*cmds);
			if (!ft_memcmp(cmds[0]->cmds[i], "-n", 2))
			{
				if (is_echo_newline(cmds[0]->cmds[i]))
					break ;
				else
					no_newline = 1;
			}
			i++;
		}
		while (cmds[0]->cmds[i])
		{
			no_quote(*cmds);
			if (cmds[0]->data.pipe_out != -1)
				ft_putstr_fd(cmds[0]->cmds[i], cmds[0]->data.pipe_out);
			else
				ft_putstr_fd(cmds[0]->cmds[i], 1);
			if (cmds[0]->cmds[i + 1])
			{
				if (cmds[0]->data.pipe_out != -1)
					ft_putstr_fd(" ", cmds[0]->data.pipe_out);
				else
					ft_putstr_fd(" ", 1);
			}
			i++;
		}
		if (!no_newline)
		{
			if (cmds[0]->data.pipe_out != -1)
				ft_putstr_fd("\n", cmds[0]->data.pipe_out);
			else
				ft_putstr_fd("\n", 1);
		}
	}
}

/* void	echo_line(t_token *current)
{
	if (!current->next)
		return ;
	if (!ft_strncmp(current->token, "echo", 5) && \
		!ft_strncmp(current->next->token, "-n", 3))
	{
		if (current->next->next)
		current = current->next->next;
		while (current)
		{
			ft_putstr_fd(current->token, 1);
			if (current->next)
				ft_putstr_fd(" ", 1);
			current = current->next;
		}
	}
	else
		echo_newline(current);
} */

int	echo(t_cmds *cmds)
{
	echo_newline(&cmds);
	return (1);
}
