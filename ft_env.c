/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:31:42 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/25 09:55:50 by ltressen         ###   ########.fr       */
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
		data->env_cpy[i] = ft_strdup(env[i]);//(data->env_cpy[i], env[i], ft_strlen(env[i]));
		i++;
	}
	/*i = 0;
	while (data->env->env_cpy[i])
	{
		ft_printf("%s\n", data->env->env_cpy[i++]);
	}*/
}