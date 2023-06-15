/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:17:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/15 20:28:34 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"

extern char test[20];

typedef struct s_data
{
	char	*env; 
	char	*input;
	char	*output;
	int		fd_in;
	int		fd_out;
}	t_data;

typedef struct s_cmds
{
	char	**cmds;
	t_data	data;
}	t_cmds;

char	*escape_quote(t_token *token);
void	no_quote(t_token *token);
int		is_symbol(t_token *token);
int		check_first_token(t_token	*token);
int		get_grammar(t_token *token);
int		is_word(t_token *token);
void	parse_tokens(t_tokens *tokens, t_cmds **cmds, char **envp);
int		is_input_redirect(t_token *token);
int		is_output_redirect(t_token *token);
int		is_the_word(t_token *token);
int		count_commands(t_tokens	*tokens);
t_cmds	**init_list_commands(t_tokens *tokens);
void	free_parse(t_cmds **cmds);
void	input_redirection(t_cmds **red, char **envp);
void	output_redirection_renew(t_cmds **red, char **envp);
void	redirect_io(int input, int output);
#endif