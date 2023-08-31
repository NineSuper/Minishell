/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:40:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/25 15:14:45 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_ff;

void	ft_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf("\n");
		rl_redisplay();
		if (g_ff == 1)
		{
			ft_printf("\033[999D  ");
			ft_printf("\033[999D");
			waitpid(-1, NULL, 0);
		}
		return ;
	}
	else if (signal == SIGQUIT)
	{
		if (g_ff == 1)
		{
			ft_printf("\033[999D  ");
			ft_printf("\033[999D");
			waitpid(-1, NULL, 0);
		}
		ft_printf("\033[2D  ");
		ft_printf("\033[2D");
	}
}
