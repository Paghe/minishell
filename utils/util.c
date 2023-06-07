/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:49:08 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/07 19:38:09 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

int	ms_whitespace(char input)
{
	if (input >= 0 && input <= 32)
		return (1);
	return (0);
}

void	remove_token(t_token *tokens)
{
	free(tokens->token);
	free(tokens);
	tokens = NULL;
}
