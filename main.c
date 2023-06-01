/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/01 15:35:04 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lexer.h"

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
		change_dir(envp, lexer.tokens);
		free(input);
		destroy_tokens(lexer.tokens);
	}
	return (0);
}
