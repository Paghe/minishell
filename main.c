/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/15 12:58:37 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/control.h"
#include "include/parse.h"

void	leaks(void)
{
	system("leaks minishell");
}



char *
rl_gets (char *line_read)
{
  /* If the buffer has already been allocated, return the memory
     to the free pool. */
  if (line_read)
    {
      free (line_read);
      line_read = (char *)NULL;
    }

  /* Get a line from the user. */
  line_read = readline ("minishell 🚀 ");

  /* If the line has any text in it, save it on the history. */
  if (line_read && *line_read)
    add_history (line_read);

  return (line_read);
}


int execute(char **envp)
{
	int exec_code;
	t_lexer	lexer;
	t_cmds	**cmds;
	char	*input;
	
	signal(SIGINT, cntr_handler);
	cmds = NULL;
	exec_code = 0;
	while (1)
	{
		clear_line();
		input = readline("minishell: ");
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
		built_in(lexer.tokens, envp);
		if (!get_grammar(lexer.tokens->front))
		{
			destroy_tokens(lexer.tokens);
			//free(input);
			return (0);
		}
		cmds = init_list_commands(lexer.tokens);
		parse_tokens(lexer.tokens, cmds, envp);
		add_history(input);
		destroy_tokens(lexer.tokens);
		free_parse(cmds);
	}
	return (exec_code);
}
char test[20];
int	main(int argc, char **argv, char **envp)
{
	int code;
	(void)argc;
	(void)argv;
	
	//input = NULL;
	if ((code = execute(envp)) == -1)
		return (-1);
	//ft_memset(input, 0, sizeof(input));
	
	return (0);
}
