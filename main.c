/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/19 20:24:40 by apaghera         ###   ########.fr       */
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
	/* def_type_tok(lexer.tokens->front); */
	/* print_token(lexer.tokens); */
	free(input);
/* 	system("leaks minishell"); */
/* 	destroy_tokens(lexer.tokens); */
	return (0);
}
