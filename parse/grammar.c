/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:34:03 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/06 17:49:43 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	check_first_token(t_token	*token)
{
	t_token	*current;

	current = token;
	if (is_word(current) || is_symbol(current))
		return (1);
	else
	{
		printf("ERROR1\n");
		return (0);
	}
}

int	is_pipe(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->type == PIPE)
	{
		if (current->next->type == WORD || is_symbol(current))
			return (1);
	}
	if (is_word(current) || is_symbol(current))
		return (1);
	return (0);
}

int	get_symbol(t_token *token)
{
	t_token	*current;

	current = token;
	if (is_symbol(current))
	{
		if (current->next->type == WORD)
			return (1);
	}
	if (is_word(current) || current->type == PIPE)
		return (1);
	return (0);
}

int	get_grammar(t_token *token)
{
	t_token	*current;

	current = token;
	check_first_token(current);
	while (current && current->next)
	{
		if (!get_symbol(current))
		{
			printf("ERROR2\n");
			return (0);
		}
		if (!is_pipe(current))
		{
			printf("ERROR3\n");
			return (0);
		}
		current = current->next;
	}
	if (is_word(current))
		return (1);
	else
	{
		printf("ERROR4\n");
		return (0);
	}
}
