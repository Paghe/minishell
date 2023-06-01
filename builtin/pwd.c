/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:10:29 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/01 19:14:40 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	build_pwd(t_tokens *tokens)
{
	char	*pwd;

	if (!ft_strncmp(tokens->front->token, "pwd", 4))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			ft_putstr_fd("error", 2);
			return ;
		}
		printf("%s\n", pwd);
	}
}
