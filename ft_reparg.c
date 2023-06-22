/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reparg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:35:29 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/22 16:35:54 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_reparg(t_data *data, int i, int j)
{
	char *res;
	int k;
	int l;

	k = j;
	while(data->cmd_full[i][j] != ' ' && data->cmd_full[i][j])
		j++;
	res = malloc(j +1);
	j = 0;
	while (data->cmd_full[i][k] != ' ')
	{
		res[j] = data->cmd_full[i][k];
		k++;
		j++;
	}
	res[j] = '\0';
	j = 0;
	while (data->env_cpy[j])
	{
		k = 0;
		if (!ft_strncmp(data->env_cpy[j], res, ft_strlen(res)))
		{
			while (data->env_cpy[j][k] != '=')
				k++;
			l = ++k;
			if (data->env_cpy[j][k])
			{
				while (data->env_cpy[j][k])
					k++;
				free(res);
				res = malloc(k - l + 1);
				k = 0;
				while (data->env_cpy[j][l])
				{
					res[k] = data->env_cpy[j][l];
					k++;
					l++;
				}
				res[k] = '\0';
				return (res);
			}
		}
		j++;
	}
	return (res);

}