/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/05 20:22:03 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parse.h"

void leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_lexer	lexer;

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
		parsing(&lexer, input);
		built_in(lexer.tokens, envp);
		chek_first_token(lexer.tokens->front);
		free(input);
		destroy_tokens(lexer.tokens);
	}
	return (0);
}
