/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:47:20 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/18 11:40:17 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	redirect_io(int input, int output)
{
	if (input)
		dup2(input, STDIN_FILENO);
	if (output)
		dup2(output, STDOUT_FILENO);
}
