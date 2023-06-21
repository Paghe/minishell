/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:15:04 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/21 11:06:23 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

int	if_is_builtin(t_tokens *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens->front;
	while (current->token[i])
	{
		current->token[i] = ft_tolower(current->token[i]);
		i++;
	}
	i = 0;
	if (!ft_strncmp(current->token, "echo", 5))
		return (1);
	if (!ft_strncmp(current->token, "cd", 3))
		return (1);
	if (!ft_strncmp(current->token, "env", 4))
		return (1);
	if (!ft_strncmp(current->token, "pwd", 4))
		return (1);
	if (!ft_strncmp(current->token, "unset", 6))
		return (1);
	return (0);
}

int	built_in(t_tokens *tokens, char **env)
{
	int	flag;

	flag = 0;
	if (echo(tokens))
		flag = 1;
	if (change_dir(env, tokens))
		flag = 1;
	if (get_env(tokens, env))
		flag = 1;
	if (build_pwd(tokens))
		flag = 1;
	return (flag);
}
