/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:27:24 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/20 19:33:36 by apaghera         ###   ########.fr       */
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

void	echo_newline(t_token *current)
{
	int		no_newline;
	int		i;

	no_newline = 0;
	i = 0;
	while (current->token[i])
	{
		current->token[i] = ft_tolower(current->token[i]);
		i++;
	}
	i = 0;
	if (!ft_strncmp(current->token, "echo", 5) && !current->next)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (!ft_strncmp(current->token, "echo", 5))
	{
		if (current->next)
			current = current->next;
		while (current && current->type != DQUOTE && current->type != SQUOTE && !ft_memcmp(current->token, "-n", 2))
		{
			if (!ft_memcmp(current->token, "-n", 2))
			{
				if (is_echo_newline(current->token))
					break ;
				else
					no_newline = 1;
			}
			current = current->next;
		}
		while (current)
		{
			ft_putstr_fd(current->token, 1);
			if (current->next)
				ft_putstr_fd(" ", 1);
			current = current->next;
		}
		if (!no_newline)
			ft_putstr_fd("\n", 1);
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

int	echo(t_tokens *tokens)
{
	t_token	*current;

	current = tokens->front;
	no_quote(current);
	echo_newline(current);
	return (1);
}
