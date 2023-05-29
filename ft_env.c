/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:31:42 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/29 14:29:01 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getenv(t_data *data, char **env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	data->env_cpy = malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		data->env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
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
}