/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:34:12 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/08 16:52:36 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

t_cmds	**init_list_commands(t_tokens *tokens, t_cmds **cmds)
{
	int		i;
	int		total_commands;
	int		len;
	t_token	*current;

	i = 0;
	total_commands = count_commands(tokens);
	cmds = malloc(sizeof(t_cmds *) * total_commands);
	current = tokens->front;
	while (i < total_commands)
	{
		cmds[i] = malloc(sizeof(t_cmds));
		len = 0;
		while (current && current->type != PIPE)
		{
			len++;
			current = current->next;
		}	
		cmds[i]->cmds = malloc(sizeof(char *) * (len + 1));
		i++;
	}
	return (cmds);
}
