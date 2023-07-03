/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:42 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/03 10:23:03 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_alpha(t_data *data)
{
	int		i;
	int		j;
	int		pos;
	char	**new_cpy;

	i = 0;
	new_cpy = ft_calloc((data->env_len + 1), sizeof(char *));
	while (i < data->env_len)
	{
		pos = 0;
		j = 0;
		while (j < data->env_len)
		{
			if (ft_strncmp(data->env_cpy[i], data->env_cpy[j], 10000) > 0)
				pos++;
			j++;
		}
		new_cpy[pos] = ft_strdup(data->env_cpy[i]);
		i++;
	}
	i = 0;
	while (i < data->env_len)
	{
		ft_printf("%s\n", new_cpy[i]);
		free(new_cpy[i]);
		i++;
	}
	free(new_cpy);
}

void	ft_export(t_data *data, char *prompt)
{
	int		i;
	char	**sp;
	char	**new_cpy;
	int		j;

	j = 0;
	sp = ft_split(prompt, ' ');
	i = 1;
	if (!sp[1])
		ft_env_alpha(data);
	while (sp[i])
	{
		while (data->env_cpy[j])
		{
			if (!strncmp(data->env_cpy[j], sp[i], ft_lenvar(sp[i]) + 1))
			{
				free(data->env_cpy[j]);
				data->env_cpy[j] = sp[i];
				break ;
			}
			j++;
		}
		if (!data->env_cpy[j])
		{
			data->env_len++;
			new_cpy = ft_calloc((data->env_len + 1), sizeof(char *));
			j = 0;
			while (data->env_cpy[j])
			{
				new_cpy[j] = ft_strdup(data->env_cpy[j]);
				free (data->env_cpy[j]);
				j++;
			}
			free(data->env_cpy);
			new_cpy[j] = ft_strdup(sp[i]);
			free(sp[i]);
			data->env_cpy = new_cpy;
		}
		i++;
	}
	ft_freesplit(sp);
}

int	ft_lenvar(char *varName)
{
	int	i;

	i = 0;
	while (varName[i] != '=' && varName[i] != '\0')
		i++;
	return (i);
}
