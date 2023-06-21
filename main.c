/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/21 16:20:35 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/control.h"
#include "include/parse.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	execute_cmd(t_cmds *cmds, char **envp)
{
	pid_t	pid;

	cmds->data.fd_in = open(cmds->data.input, O_RDONLY);
	cmds->data.fd_out = open(cmds->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644); // opening here file doesn't matter the order
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		redirect_io(cmds->data.fd_in, cmds->data.fd_out); // dup2(input, STDIN_FILENO); // dup2(output, STDOUT_FILENO);												 // dup2(output, STDOUT_FILENO);
		close(cmds->data.fd_in);
		close(cmds->data.fd_out);
		execve(cmds->data.env, cmds->cmds, envp);
	}
	else
		waitpid(pid, NULL, 0);
	return ;
}

void	execute_cmds(t_cmds **cmds, char ***envp)
{
	int		i;
	char	*var_name;
	char	*value;

	i = 0;

	var_name = NULL;
	value = NULL;
	while (cmds[i])
	{
		if (ft_strncmp(cmds[i]->cmds[0], "unset", 5) == 0)
			unset(envp, cmds[i]->cmds[1]);
		else if (is_env_var(cmds[i]->cmds[0], &var_name, &value))
		{
			//if (setenv(var_name, value, 1) == -1)
			//	perror("setenv");
			set_env_var(envp, var_name, value);
			free(var_name);
			free(value);
		}
		else
			pipe_proccess(&cmds[i], *envp, cmds);
		//execute_cmd(cmds[i], envp); // execute multiple cmds;
		if (cmds[i]->data.env)
			free(cmds[i]->data.env);
		i++;
	}
	//while (j != i - 1) //save status of last
	//{
	//	waitpid(struct pid, NULL, 0);
	//	j++;
	//}
}

int	execute(char **envp)
{
	int		exec_code;
	t_lexer	lexer;
	t_cmds	**cmds;
	char	*input;

	signal(SIGINT, cntr_handler);
	signal(SIGQUIT, cntr_handler);
	cmds = NULL;
	exec_code = 0;
	while (1)
	{
		clear_line();
		input = readline("minishell 🚀 ");
		if (!input)
		{
			exec_code = -1;
			break ;
		}
		if (input && input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		parsing(&lexer, ft_strdup(input));
		free(input);
		if (!get_grammar(lexer.tokens))
		{
			destroy_tokens(lexer.tokens);
			return (0);
		}
		cmds = init_list_commands(lexer.tokens);
		parse_tokens(lexer.tokens, cmds, envp);
		// replace_env_vars(cmds, envp);
		execute_cmds(cmds, &envp);
		destroy_tokens(lexer.tokens);
		free_parse(cmds);
	}
/* 	free_env(envp); */
	return (exec_code);
}

int	main(int argc, char **argv, char **envp)
{
	int	code;
	errno = 0;
	(void)argc;
	(void)argv;
	if ((code = execute(envp)) == -1)
		return (-1);
	return (0);
}
