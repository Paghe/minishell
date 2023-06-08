/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/08 16:44:46 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parse.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_lexer	lexer;
	t_cmds	*cmds;

	(void)argc;
	(void)argv;
/* 	atexit(leaks); */
	int i = 1;
	while (i)
	{
		input = readline("minishell 🚀 ");
		if (input && input[0] == '\0')
		{
			free(input);
			continue ;
		}
		parsing(&lexer, ft_strdup(input));
		built_in(lexer.tokens, envp);
		if (!get_grammar(lexer.tokens->front))
		{
			destroy_tokens(lexer.tokens);
			free(input);
			return (0);
		}
		parse_tokens(lexer.tokens, &cmds);
		add_history(input);
		destroy_tokens(lexer.tokens);
		free(input);
		i = 0;
	}
	return (0);
}
