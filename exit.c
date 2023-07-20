/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:31:30 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/04 11:43:59 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_free(t_data *data)
{
	if (data->home)
		free(data->home);
	if (data->path)
		free(data->path);
	if (data->pwd)
		free(data->pwd);
	if (data->env_cpy[0])
		ft_freesplit(data->env_cpy);
	if (data->cmd[0])
		ft_freesplit(data->cmd);
	if (data->full[0])
		ft_freesplit(data->full);
	free(data);
}

void	ft_exit(t_data *data, char *prompt)
{
	char	**sp;
	int		exit_code;

	exit_code = 0;
	if (prompt)
	{
		sp = ft_split(data->full[0], ' ');
		if (sp[1])
			exit_code = ft_atoi(sp[1]);
		free(prompt);
		ft_freesplit(sp);
		ft_printf("exit\n");
	}
	else
	{
		ft_exit_free(data);
		ft_printf("exit\n");
		exit(exit_code);
	}
	ft_exit_free(data);
	exit(exit_code);
}
