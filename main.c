/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/19 18:54:18 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lexer.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_lexer	lexer;

	(void)argc;
	(void)argv;
	input = readline("minishell 🚀 ");
	parsing(&lexer, input);
	free(input);
/* 	system("leaks minishell"); */
/* 	destroy_tokens(lexer.tokens); */
	return (0);
}
