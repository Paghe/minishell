/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:17:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/20 23:33:57 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"

# define READ_END 0
# define WRITE_END 1

typedef struct s_data
{
	char	*env;
	char	*input;
	char	*output;
	int		fd_in;
	int		fd_out;
	int		pipe_in;
	int		pipe_out;
	int		export;
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
int		begin_with_pipes(t_token *token);
int		init_pipes(t_cmds **cmds, int index);
void	close_all(t_cmds **cmds);
void	pipe_proccess(t_cmds **red, char **envp, t_cmds **all);
int		is_env_var(char *word, char	**var_name, char **value);
char	*get_env_var(char *var_name, char **envp);
void	replace_env_vars(t_cmds **cmds, char **envp);
int		count_dollars(char *word);
char	**escape_quotes_cmds(char **cmds);
int		unset(char ***envp, char *var_name);
void	print_env(char **envp);
int		set_env_var(char ***envp, char	*var_name, char *value);
void	free_env(char **envp);
void	export(char **cmds, char ***env, char ***shell_env);
char	**copy_env(char **envp);
#endif