/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/06 20:38:12 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
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

void	no_quote(t_token *token)
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

int	is_redirect(t_token *token)
{
	return (token->type == LESS || token->type == DLESS || \
		token->type == MORE || token->type == DMORE);
}

int	is_the_word(t_token *token)
{
	return (token->type == WORD || token->type == SQUOTE || \
		token->type == DQUOTE);
}

void	parse_tokens(t_tokens *tokens, t_cmds *cmds)
{
	t_token	*token;

	token = tokens->front;
	while (token)
	{
		if (is_redirect(token))
		{
			if (is_the_word(token->next))
			{
				cmds->cmd[0] = ft_strdup(token->next->token);
				printf("%s\n", cmds->cmd[0]);
			}
		}
		token = token->next;
	}
	free(cmds->cmd[0]);
}
