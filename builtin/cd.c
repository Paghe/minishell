/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:51 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/01 15:40:26 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	change_old(char **env)
{
	int		i;
	char	*old;

	i = 0;
	old = getcwd(NULL, 0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
		{
			env[i] = ft_strjoin("OLDPWD=", old);
			free(old);
			return ;
		}
		i++;
	}
	free(old);
}

char	*get_path(t_tokens *tokens)
{
	char	*tmp;
	char	*path;
	char	*dir;

	path = getcwd(NULL, 0);
	tmp = ft_strjoin(path, "/");
	dir = ft_strjoin(tmp, tokens->front->next->token);
	free(path);
	free(tmp);
	return (dir);
}

void	change_current_pwd(char **env)
{
	char	*current;
	int		i;

	i = 0;
	current = getcwd(NULL, 0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			env[i] = ft_strjoin("PWD=", current);
			free(current);
			return ;
		}
		i++;
	}
	free(current);
}

void	change_dir(char **env, t_tokens *tokens)
{
	char	*dir;
	int		i;

	i = 0;
	if (!ft_strncmp(tokens->front->token, "cd", 3))
	{
		change_old(env);
		dir = get_path(tokens);
		if (chdir(dir) != 0)
		{
			ft_putstr_fd("error\n", 2);
			free(dir);
			return ;
		}
		change_current_pwd(env);
		free(dir);
	}
}
