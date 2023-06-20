/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:35:30 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/20 14:36:25 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
todo si $ARG existe dans ENV alors : unset: arg: invalid parameter name
*/

void	ft_cpy_env(t_data *data, int i)
{
	char	**unset_cpy;
	int		j;
	int		k;

	unset_cpy = ft_calloc(data->env_len + 1, sizeof(char *));
	j = 0;
	k = 0;
	while (data->env_cpy[j])
	{
		if (i == j)
			j++;
		if (data->env_cpy[j])
			unset_cpy[k++] = ft_strdup(data->env_cpy[j++]);
	}
	ft_freesplit(data->env_cpy);
	data->env_cpy = unset_cpy;
}

int	ft_arg_unset(t_data *data, char *arg)
{
	int	i;

	i = -1;
	arg = ft_strjoin(arg, "=");
	while (data->env_cpy[++i])
		if (!ft_strncmp(data->env_cpy[i], arg, ft_strlen(arg)))
			break ;
	ft_cpy_env(data, i);
}

int	ft_unset(t_data *data, char *prompt)
{
	char	**split;
	int		i;

	split = ft_split(prompt, ' ');
	i = 0;
	if (!split[1])
		return (printf("unset: not enough arguments\n"));
	while (split[++i])
		ft_arg_unset(data, split[i]);
}
