/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:59:13 by crepou            #+#    #+#             */
/*   Updated: 2023/06/18 15:42:47 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

int	is_env_var(char *word, char	**var_name, char **value)
{
	char	*after_eq;
	int		index_bef_eq;
	int		i;

	after_eq = ft_strchr(word, '=');
	if (after_eq)
	{
		i = 0;
		index_bef_eq = after_eq - word;
		(*var_name) = (char *)malloc(sizeof(char) * index_bef_eq + 2);
		(*value) = (char *)malloc(sizeof(char) * ft_strlen(word) - index_bef_eq - 1);
		ft_strlcat((*var_name), word, index_bef_eq + 1);
		ft_strlcat((*value), after_eq + 2, ft_strlen(word) - index_bef_eq - 2);
		return (1);
	}
	return (0);
}

char	*get_env_var(char *var_name)
{
	char	*value;

	value = getenv(var_name);
	if (value)
		return (value);
	value = "";
	return (value);
}