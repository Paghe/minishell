/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/30 14:22:57 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

char	*escape_quote(t_token *token)
{
	int		i;
	int		j;
	char	*new_token;

	i = 0;
	j = 0;
	if (token->token[i] == '\"' || token->token[i] == '\'')
		i++;
	j = i;
	while (token->token[i] && \
		(token->token[i] != '\'' && token->token[i] != '\"'))
		i++;
	new_token = ft_substr(token->token, j, i - j);
	return (new_token);
}

void	test_(t_token *token)
{
	t_token	*new_token;
	char	*tmp;

	new_token = token;
	while (new_token)
	{
		tmp = escape_quote(new_token);
		free(new_token->token);
		new_token->token = tmp;
		new_token = new_token->next;
	}
	new_token = token;
}
