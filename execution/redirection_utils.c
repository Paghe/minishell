/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:19:33 by crepou            #+#    #+#             */
/*   Updated: 2023/06/19 18:15:55 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_env_path(char **envp, char *command)
{
	char	*path;
	char	*cmd_path;
	int		i;
	char	**paths;
	char	*cmd;

	i = -1;
	while (envp[++i])
	{
		if (envp[i] == ft_strnstr(envp[i], "PATH", 4))
			path = ft_strdup(envp[i]);
	}
	paths = ft_split(path + 5, ':');
	if (command && ft_strrchr(command, '/'))
		cmd = strrchr(command, '/') + 1;
	else
		cmd = command;
	free(path);
	i = -1;
	while (paths[++i])
	{
		cmd_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		strcpy(cmd_path, paths[i]); // Implement strcpy
		strcat(cmd_path, "/");	// Implement strcat
		strcat(cmd_path, cmd);
		// printf("%s\n", cmd_path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_paths(paths); // free stuff looks above
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_paths(paths);
	return (NULL); // this way is way faster to allocate memory 
}

t_redirection	fill_redirection_struct(char *command, char *filename, char **args, char **envp)
{
	t_redirection		red;
	int					i;
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
