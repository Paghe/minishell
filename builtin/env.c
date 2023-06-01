/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:55:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/01 19:01:12 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	get_env(t_tokens *tokens, char **env)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tokens->front->token, "env", 4))
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}
