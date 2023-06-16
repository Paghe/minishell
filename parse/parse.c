/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/16 15:27:16 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/lexer.h"
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
		if (current->type == PIPE)
		{
			i++;
			current = current->next;
			j = 0;
		}
		if (is_input_redirect(current))
		{
			if (current->next && is_the_word(current->next))
			{
				if (cmds[i]->data.env)
					free(cmds[i]->data.env);
				cmds[i]->data.input = ft_strdup(current->next->token);
				cmds[i]->data.env = get_env_path(envp, cmds[i]->cmds[0]);
				current = current->next;
			}
		}
		else if (is_output_redirect(current))
		{
			if (current->next && is_the_word(current->next))
			{
				if (cmds[i]->data.env)
					free(cmds[i]->data.env);
				cmds[i]->data.output = ft_strdup(current->next->token);
				cmds[i]->data.env = get_env_path(envp, cmds[i]->cmds[0]); //free
				fd = open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd);
				current = current->next;
			}
		}
		else
		{
			cmds[i]->cmds[j] = ft_strdup(current->token);
/*			printf("CMD: %s\n", cmds[i]->cmds[j]);*/
			j++;
			cmds[i]->cmds[j] = NULL;
		}
		if (current)
			current = current->next;
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
		{
			free(cmds[i]->data.output);		
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

//cmds[0]->cmds[0] = wc
//cmds[0]->cmds[1] = arg: -l
//cmds[0]->cmd[2] = NULL;
//redirect_io(t_cmds)
//{
//	open(data.input)
//}