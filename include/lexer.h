/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:53:59 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/15 22:00:52 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_token	t_token;

typedef struct s_token
{
	char	*token;
	char	*type;
	t_token	*next;
}	t_token;

typedef struct s_tokens
{
	t_token	*front;
	t_token	*rear;
	size_t	size;
}	t_tokens;

typedef struct s_lexer
{
	int			argc;
	char		**argv;
	t_tokens	*tokens;
}	t_lexer;

t_tokens	*create_tokens(void);
t_token		*new_token(char *format, char *type);
void		add_token(t_tokens *tokens, char *format, char *type);
int			whitespace(char input);
void		parsing(t_lexer *lexer, char *input);
#endif