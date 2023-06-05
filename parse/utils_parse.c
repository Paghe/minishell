/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:40:36 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/05 20:01:11 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	is_symbol(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->type == DQUOTE || current->type == SQUOTE || \
			current->type == DMORE || current->type == DLESS || \
				current->type == LESS || current->type == MORE)
		return (1);
	return (0);
}
