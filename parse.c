/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:38:43 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/03 17:42:49 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char *prompt)
{
	if (prompt)
		free(prompt);
	else
	{
		free(data->home);
		free(data->pwd);
		ft_freesplit(data->env_cpy);
		free(data);
		exit(1);
	}
	free(data->home);
	ft_freesplit(data->env_cpy);
	ft_freesplit(data->cmd);
	ft_freesplit(data->cmd_full);
	free(data->pipes);
	free(data->pwd);
	free(data);
	exit(1);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}
