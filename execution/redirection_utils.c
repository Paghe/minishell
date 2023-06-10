/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:19:33 by crepou            #+#    #+#             */
/*   Updated: 2023/06/08 22:45:43 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

char	*get_env_path(char **envp, char *command)
{
	char	*path;
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (envp[i] == ft_strnstr(envp[i], "PATH", 4))
			path = ft_strdup(envp[i]);
	}
	paths = ft_split(path + 5, ':');
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(ft_strjoin(paths[i], "/"), command);
		if (access(paths[i], X_OK) == 0)
			return (paths[i]);
	}
	return (NULL);
}

t_redirection	fill_redirection_struct(char *command, char *filename, char **args, char **envp)
{
	t_redirection	red;
	int				i;
	const char			*env[2];

	red.filename = filename;
	i = 0;
	while (args[i])
		i++;
	red.args = (const char **)malloc(sizeof(const char *) * (i + 2));
	red.args[0] = get_env_path(envp, command);
	i = 0;
	while (args[i])
	{
		red.args[i + 1] = ft_strdup(args[i]);
		i++;
	}
	red.args[i + 1] = NULL;
	env[0] = red.args[0];
	env[1] = NULL;
	red.envp = env;
	return (red);
}
