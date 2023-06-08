/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/08 16:46:31 by apaghera         ###   ########.fr       */
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

int	count_commands(t_tokens	*tokens)
{
	t_token	*current;
	int		count;

	count = 1;
	current = tokens->front;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	parse_tokens(t_tokens *tokens, t_cmds **cmds)
{
	t_token	*current;
	int		i;

	current = tokens->front;
	i = 0;
	cmds = init_list_commands(tokens, cmds);
	while (current)
	{
		if (is_redirect(current))
		{
			printf("REDIR: %s\n", current->token);
			if (current->next && is_the_word(current->next))
			{
				cmds[i]->cmds[i] = ft_strdup(current->next->token);
				printf("%s\n", cmds[i]->cmds[i]);
			}
		}
		current = current->next;
		printf("%i\n", i);
		i++;
	}
}



