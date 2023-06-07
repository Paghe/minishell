/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:04:10 by crepou            #+#    #+#             */
/*   Updated: 2023/06/07 19:37:07 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/control.h"

void	clear_line(void)
{
	struct termios	terminal_args;

	tcgetattr(1, &terminal_args);
	terminal_args.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &terminal_args);
}

void	cntr_handler(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
