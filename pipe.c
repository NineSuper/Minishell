/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:37:16 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/06 10:15:29 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_ff;

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipes[i])
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

pid_t	ft_piping(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		g_ff = 1;
		if (i == 0)
			dup2(data->pipes[i][1], 1);
		else if (i == data->pipenum - 1)
			dup2(data->pipes[i - 1][0], 0);
		else
		{
			dup2(data->pipes[i - 1][0], 0);
			dup2(data->pipes[i][1], 1);
		}
		close_pipes(data);
		ft_exec(data, i, 1);
	}
	return (pid);
}

void	ft_go_pipe(t_data *data, int i)
{
	while (data->full[i])
	{
		ft_piping(data, i);
		i++;
	}
	close_pipes(data);
	i = 0;
	while (i < data->pipenum)
	{
		waitpid(-1, &data->errnum, 0);
		i++;
	}
	g_ff = 0;
	ft_freesplit((char **)data->pipes);
}
