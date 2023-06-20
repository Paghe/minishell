/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:15:04 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/19 19:24:01 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

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
