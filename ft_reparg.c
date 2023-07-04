/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reparg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:35:29 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/03 14:24:29 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_reparg(t_data *data, int i, int j)
{
	char	*res;
	int		k;

	k = j;
	while (data->cmd_full[i][j] != ' ' && data->cmd_full[i][j])
		j++;
	res = malloc(j - k + 1);
	j = 0;
	k++;
	while (data->cmd_full[i][k] != ' ' && data->cmd_full[i][k] != '"'
		&& data->cmd_full[i][k] != '\'' && data->cmd_full[i][k])
		res[j++] = data->cmd_full[i][k++];
	res[j] = '\0';
	j = 0;
	while (data->env_cpy[j])
	{
		if (!ft_strncmp(data->env_cpy[j], res, ft_strlen(res)))
			ft_get_arg(data, j, res);
		j++;
	}
	if (res)
		free(res);
	return (ft_calloc(1, 1));
}

char	*ft_get_arg(t_data *data, int j, char *res)
{
	int	k;
	int	l;

	k = 0;
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
	return (NULL);
}
