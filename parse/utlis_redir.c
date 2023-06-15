/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:47:20 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/15 15:28:08 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

t_cmds	**fill_up_cmds(t_tokens *tokens, t_cmds **cmds, char **envp)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens->front;
	while (current)
	{
		cmds[i]->data.fd_in = -1;
		cmds[i]->data.fd_out = -1;
		if(current->type == PIPE)
		{
			printf("PIPE\n", current->token);
			current = current->next;
			i++;
		}
		if (is_input_redirect(current) && current->next)
		{
			if (cmds[i]->data.input)
				free(cmds[i]->data.input);
			cmds[i]->data.input = ft_strdup(current->next->token);
			cmds[i]->data.fd_in = open(cmds[i]->data.input, O_RDONLY);
			current = current->next
		}
		else if (is_output_redirect(current) && current->next)
		{
			if (cmds[i]->data.output)
				free(cmds[i]->data.output);
			cmds[i]->data.output = ft_strdup(current->next->token);
			cmds[i]->data.fd_out = open(cmds[i]->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			current = current->next
		}
		if (current)
			current = current->next;
		i++;
	}
	return (cmds);
}
