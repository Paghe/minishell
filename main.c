/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/30 13:26:49 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lexer.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_lexer	lexer;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell 🚀 ");
		parsing(&lexer, input);
		echo(lexer.tokens);
		free(input);
		destroy_tokens(lexer.tokens);
	}
	return (0);
}
