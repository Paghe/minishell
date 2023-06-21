/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/21 01:23:31 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

char	*escape_quote(t_token *token)
{
	int		i;
	int		j;
	char	*new_token;

	i = 0;
	j = 0;
	if (token->token[i] == '\"' || token->token[i] == '\'')
		i++;
	j = i;
	while (token->token[i] && \
		(token->token[i] != '\'' && token->token[i] != '\"'))
		i++;
	new_token = ft_substr(token->token, j, i - j);
	return (new_token);
}

void	no_quote(t_token *token)
{
	t_token	*new_token;
	char	*tmp;

	new_token = token;
	while (new_token)
	{
		tmp = escape_quote(new_token);
		free(new_token->token);
		new_token->token = tmp;
		new_token = new_token->next;
	}
	new_token = token;
}

int	count_commands(t_tokens	*tokens)
{
	t_token	*current;
	int		count;

	count = 1;
	current = tokens->front;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	parse_tokens(t_tokens *tokens, t_cmds **cmds, char **envp)
{
	t_token	*current;
	int		i;
	int		j;
	int		fd;

	current = tokens->front;
	i = 0;
	j = 0;
	while (current)
	{
		//printf("token: %s type %i is env var: %i\n", current->token, current->type, is_env_var(current->token, var_name, value));
		if (current->type == PIPE)
		{
			init_pipes(cmds, i);
			i++;
			current = current->next;
			j = 0;
		}
		if (is_input_redirect(current))
		{
			if (current->next && is_the_word(current->next))
			{
				if (cmds[i]->data.input)
					free(cmds[i]->data.input);
				cmds[i]->data.input = ft_strdup(current->next->token);
				current = current->next;
			}
		}
		else if (is_output_redirect(current))
		{
			if (current->next && is_the_word(current->next))
			{
				if (cmds[i]->data.output)
					free(cmds[i]->data.output);
				cmds[i]->data.output = ft_strdup(current->next->token);
				fd = open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd);
				current = current->next;
			}
		}
		else
		{
			if (cmds[i]->data.env)
				free(cmds[i]->data.env);
			cmds[i]->cmds[j] = ft_strdup(current->token);
			cmds[i]->data.env = get_env_path(envp, cmds[i]->cmds[0]);
			j++;
			cmds[i]->cmds[j] = NULL;
		}
		if (current)
			current = current->next;
	}
}

void	replace_env_vars(t_cmds **cmds, char **envp)
{
	int		i;
	int		j;
	char	*arg;
	char	*value;
	int		dollars;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->cmds[j])
		{
			arg = cmds[i]->cmds[j];
			dollars = count_dollars(arg);
			if ((arg = ft_strrchr(arg, '$')) && dollars % 2 != 0)
			{
				value = get_env_var(arg + 1, envp);
				arg = (char *)malloc(sizeof(char) * (dollars + 1));
				ft_strlcat(arg, cmds[i]->cmds[j], dollars);
				value = ft_strjoin(arg, value);
				free(arg);
				free(cmds[i]->cmds[j]);
				cmds[i]->cmds[j] = ft_strdup(value);
				free(value);
			}
			j++;
		}
		i++;
	}
}

void	free_parse(t_cmds **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->cmds[j])
		{
			free(cmds[i]->cmds[j]);
			j++;
		}
		free(cmds[i]->cmds);
		if (cmds[i]->data.input)
			free(cmds[i]->data.input);
		if (cmds[i]->data.output)
			free(cmds[i]->data.output);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
