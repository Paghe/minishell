/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:47:20 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/15 20:34:43 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

// t_cmds	**fill_up_cmds(t_tokens *tokens, t_cmds **cmds, char **envp)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = count_commands(tokens);
// 	while (i < count)
// 	{
// 		cmds[i]
// 		i++;
// 	}
// }

void	redirect_io(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
}