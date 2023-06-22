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
	char *str;
	char *res;
	int k;
	int l;

	k = j;
	while(data->cmd_full[i][j] && ((data->cmd_full[i][j] > 47 && data->cmd_full[i][j] < 58) ||
		(data->cmd_full[i][j] > 64 && data->cmd_full[i][j] < 91) || (data->cmd_full[i][j] > 96 && data->cmd_full[i][j] < 123)))
		j++;
	res = malloc(j - k + 1);
	res[j - k] = '\0';
	j = 0;
	while (res[j])
		res[j++] = data->cmd_full[i][k++];
	j = 0;
	while (data->env_cpy[j])
	{
		k = 0;
		str = ft_strnstr(data->env_cpy[j], res, ft_strlen(res));
		*str += ft_strlen(res);
		if (*str && *str == '=')
		{
			free(res);
			*str++;
			while (*str != '\0')
				k++;
			res = malloc(k + 1);
			k = ft_strlen(res) + 1;
			j = 0;
			while (str[k])
				res[j++] = str[k++];
			res[k] = '\0';
			break;
		}
		j++;
	}
	free(str);
	str = ft_strnstr(data->cmd_full[i], (char *)'$', 1);
	*str++;
	j = 1;
	while(*str && ((*str > 47 && *str < 58) || (*str > 64 && *str < 91) || (*str > 96 && *str < 123)))
		j++;
	free(str);
	str = malloc(ft_strlen(data->cmd_full[i]) + ft_strlen(res) - j + 1);
	str[(ft_strlen(data->cmd_full[i]) + ft_strlen(res) - j)] = '\0';
	k = 0;
	while (str[k] && data->cmd_full[i][k] != '$')
		str[k] = data->cmd_full[i][k++];
	l = 0;
	while (str[k] && res[l])
		str[k++] = res[l++];
	while (str[k] && data->cmd_full[i][k + j])
		str[k] = data->cmd_full[i][j + k++];
	free(res);
	return (str);
}