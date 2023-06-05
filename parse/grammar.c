/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:34:03 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/05 20:32:01 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"


int	chek_first_token(t_token	*token)
{
	t_token	*current;

	current = token;
	if (token->type == WORD || is_symbol(token))
		return (1);
	else
	{
		printf("ERROR\n");
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
	return (0);
}

void	get_grammar(t_token *token)
{
	t_token	*current;

	current = token;
	check_first_token(current);
	while (current)
	{
		current = current->next;
	}
}