/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:48:23 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/16 20:05:35 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

char	*divide_words(char *input, int *spaces)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while (whitespace(input[i]))
		i++;
	j = i;
	*spaces = i;
	while (!whitespace(input[i]))
		i++;
	token = malloc(sizeof(char) * i - j + 1);
	i = 0;
	while (!whitespace(input[j + i]))
	{
		token[i] = input[j + i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

void	parsing(t_lexer *lexer, char *input)
{
	int		i;
	int		spaces;
	char	*tmp;

	i = 0;
	spaces = 0;
	lexer->tokens = create_tokens();
	while (input[i])
	{
		tmp = divide_words(input + i, &spaces);
		i += ft_strlen(tmp) + spaces;
		if (!tmp)
			break ;
		add_token(lexer->tokens, tmp, tmp);
	}
	while (lexer->tokens->front->next)
	{
		printf("%s\n", lexer->tokens->front->token);
		lexer->tokens->front = lexer->tokens->front->next;
	}
}
