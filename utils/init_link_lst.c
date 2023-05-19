/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_link_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:00:08 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/19 13:57:24 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

t_tokens	*create_tokens(void)
{
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->front = NULL;
	tokens->rear = NULL;
	tokens->size = 0;
	return (tokens);
}

t_token	*new_token(char *format, char *type)
{
	t_token	*new_token;
	char	*new_format;
	char	*new_type;

	new_format = ft_strdup(format);
	new_type = ft_strdup(type);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = new_format;
	new_token->type = new_type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_tokens *tokens, char *format, char *type)
{
	t_token	*token;
	
	if (!format || !type)
		return ;
	token = new_token(format, type);
	if (!token)
		return ;
	if (tokens->size == 0)
	{
		tokens->front = token;
		tokens->rear = token;
	}
	else
	{
		tokens->rear->next = token;
		tokens->rear = tokens->rear->next;
	}
	tokens->size++;
}

void	destroy_tokens(t_tokens *tokens)
{
	while (tokens->front)
	{
		remove_token(tokens->front);
		tokens->front = tokens->front->next;
		tokens->size--;
	}
	tokens->rear = NULL;
	free(tokens);
}
