/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:31:42 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/28 14:08:28 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getenv(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env_len = i;
	data->env_cpy = ft_calloc(i + 1 ,sizeof(char *));
	i = 0;
	while (env[i])
	{
		data->env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
}

void	ft_gethome(t_data *data)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(data->pwd, '/');
	// if (data->home && split[0])
	// 	free (data->home);
	data->home = ft_strdup("/");
	while (split[++i] && i < 3)
	{
		data->home = ft_strjoin(data->home, split[i]);
		if (i < 2)
			data->home = ft_strjoin(data->home, "/");
	}
	ft_freesplit(split);
}
