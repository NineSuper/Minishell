/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:31:30 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/27 11:27:53 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_free(t_data *data)
{
	free(data->home);
	free(data->path);
	ft_freesplit(data->env_cpy);
	ft_freesplit(data->cmd);
	ft_freesplit(data->full);
	free(data->pwd);
	free(data);
}

int	is_str_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf("%s: numeric argument required", str);
			return (2);
		}
		i++;
	}
	return (ft_atoi(str));
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
			exit_code = is_str_alpha(sp[1]);
		free(prompt);
		ft_freesplit(sp);
	}
	else
	{
		exit_code = data->errnum;
		free(data->home);
		free(data->pwd);
		free(data->path);
		ft_freesplit(data->env_cpy);
		free(data);
		exit(exit_code);
	}
	ft_exit_free(data);
	exit(exit_code);
}
