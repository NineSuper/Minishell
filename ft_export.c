/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:42 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/31 17:27:26 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, char *prompt)
{
	int	i;
	char	**sp;
	char	**new_cpy;
	int	j;

	j = 0;
	sp = ft_split(prompt, ' ');
	i = 1;
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
	free(sp[0]);
	free(sp);
}

void	ft_unset(t_data *data, char *prompt)
{
	int	i;
	char	**sp;
	char	**new_cpy;
	int	j;
	int	k;

	sp = ft_split(prompt, ' ');
	i = 1;
	while (sp[i])
	{	
		j = 0;
		while (data->env_cpy[j])
		{
			if (!strncmp(data->env_cpy[j], sp[i], ft_lenvar(sp[i])))
				break ;
			j++;
		}
		if (data->env_cpy[j])
		{	
			data->env_len--;
			new_cpy = ft_calloc((data->env_len + 1), sizeof(char *));
			j = 0;
			k = 0;
			while (data->env_cpy[j])
			{
				if (!strncmp(data->env_cpy[j], sp[i], ft_lenvar(sp[i])))
//				{
//					free(data->env_cpy[j]);
					j++;
//				}
				if (data->env_cpy[j])
				{
					new_cpy[k] = ft_strdup(data->env_cpy[j]);
//					free (data->env_cpy[j]);
				}
				j++;
				k++;
			}
//			free(data->env_cpy);
			data->env_cpy = new_cpy;
		}
		i++;
		ft_printf("%d", data->env_len);
//		free(sp[0]);
//		free(sp);
	}
}

int	ft_lenvar(char *varName)
{
	int	i;

	i = 0;
	while (varName[i] != '=' && varName[i] != '\0')
		i++;
	return (i);
}
