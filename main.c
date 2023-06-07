/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/07 15:28:03 by apaghera         ###   ########.fr       */
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
/* 	t_cmds	cmds; */

	(void)argc;
	(void)argv;
/* 	atexit(leaks); */
/* 	while(envp[j])
	{
		printf("%s\n", envp[j]);
		j++;
	} */
	while (1)
	{
		input = readline("minishell 🚀 ");
		if (input && input[0] == '\0')
		{
			free(input);
			continue ;
		}
		parsing(&lexer, input);
		built_in(lexer.tokens, envp);
		if (!get_grammar(lexer.tokens->front))
		{
			free(input);
			destroy_tokens(lexer.tokens);
			return (0);
		}
		/* parse_tokens(lexer.tokens, &cmds); */
		add_history(input);
		free(input);
		destroy_tokens(lexer.tokens);
	}
	return (0);
}
