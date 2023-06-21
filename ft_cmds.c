/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:40:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/06 15:04:22 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		ft_readline();
	}
	else if (signal == SIGQUIT)
		ft_printf("");
}