/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:31:30 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/04 11:29:17 by jcasades         ###   ########.fr       */
=======
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:31:30 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/04 11:43:59 by ltressen         ###   ########.fr       */
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_free(t_data *data)
{
	free(data->home);
	free(data->path);
	ft_freesplit(data->env_cpy);
	ft_freesplit(data->cmd);
	ft_freesplit(data->cmd_full);
	free(data->pipes);
	free(data->pwd);
	free(data);
}

void	ft_exit(t_data *data, char *prompt)
{
	char	**sp;
<<<<<<< HEAD
	int	exit_code;
=======
	int		exit_code;
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8

	exit_code = 0;
	if (prompt)
	{
		sp = ft_split(data->cmd_full[0], ' ');
		if (sp[1])
			exit_code = ft_atoi(sp[1]);
		free(prompt);
		ft_freesplit(sp);
	}
	else
	{
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
