/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:31:42 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/30 14:55:59 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getenv(t_data *data, char **env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	data->env_len = i;
	data->env_cpy = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env[i])
	{
		data->env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	data->env_cpy[i] = NULL;
}

void	ft_gethome(t_data *data)
{
	char	**home_split;
	int		i;

	i = 0;
	while (data->env_cpy[i])
	{
		if (!ft_strncmp(data->env_cpy[i], "HOME", 4))
		{
			home_split = ft_split(data->env_cpy[i], '=');
			if (home_split[1])
				data->home = ft_strdup(home_split[1]);
			break ;
		}
		i++;
	}
	ft_freesplit(home_split);
}