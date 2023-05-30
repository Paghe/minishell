/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:27:24 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/30 15:15:35 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	echo_newline(t_token *current)
{
	if (!ft_strncmp(current->token, "echo", 5))
	{
		current = current->next;
		while (current)
		{
			printf("%s", current->token);
			printf(" ");
			current = current->next;
		}
		printf("\n");
	}
}

void	echo_line(t_token *current)
{
	if (!ft_strncmp(current->token, "echo", 5) && \
		!ft_strncmp(current->next->token, "-n", 3))
	{
		current = current->next->next;
		while (current)
		{
			printf("%s", current->token);
			if (current->next)
				printf(" ");
			current = current->next;
		}
	}
	else
		echo_newline(current);
}

void	echo(t_tokens *tokens)
{
	t_token	*current;

	current = tokens->front;
	test_(current);
	echo_line(current);
}
