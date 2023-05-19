/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:48:23 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/19 19:09:32 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	print_token(t_tokens *tokens)
{
	t_token	*current;

	current = tokens->front;
	while (current)
	{
		printf("%s\n", current->token);
		current = current->next;
	}
}

int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

void	parsing(t_lexer *lexer, char *input)
{
	int		i;
	char	buffer[4096];
	size_t	len;
	char	current;
	char	next;
	char	*line;
	char	*buf_ptr;
	int		squote;
	int		dquote;

	i = 0;
	line = ft_strtrim(input, " \t");
	len = min(ft_strlen(line), LINEBUFFER_MAX);
	ft_memcpy(buffer, line, len);
	buffer[len] = '\0';
	lexer->tokens = create_tokens();
	squote = 0;
	dquote = 0;
	buf_ptr = buffer;
	while (i < (int)len)
	{
		current = line[i];
		if (current == '\"' && !squote)
			dquote ^= 1;
		if (current == '\'' && !dquote)
			squote ^= 1;
		if (i <= (int)len)
			next = line[i + 1];
		else
			i = 0;
		if (((current == ' ' && line[i + 1] != ' ' && next) || current == '\0') && !squote && !dquote)
		{
			buffer[i] = '\0';
			add_token(lexer->tokens, buf_ptr, buf_ptr);
			buf_ptr += ft_strlen(buf_ptr) + 1;
		}
		i++;
	}
	add_token(lexer->tokens, buf_ptr, buf_ptr);
	print_token(lexer->tokens);
	free(line);
}