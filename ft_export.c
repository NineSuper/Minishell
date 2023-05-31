/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:42 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/31 11:59:28 by jcasades         ###   ########.fr       */
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
			ft_printf("ptdr\n");
			data->env_len++;
			new_cpy = malloc(sizeof(char *) * data->env_len + 1);
			j = 0;
			while (data->env_cpy[j])
			{
				new_cpy[j] = data->env_cpy[j];
				j++;
			}
			free(data->env_cpy);
			new_cpy[j] = sp[i];
			new_cpy[++j] = NULL;
			data->env_cpy = new_cpy;
		}
		i++;
	}
}

void	ft_unset(t_data *data, char *prompt)
{
	int	i;
	char	**sp;
	char	**new_cpy;
	int	j;
	int	k;

	j = 0;
	sp = ft_split(prompt, ' ');
	i = 1;
	while (sp[i])
	{
		while (data->env_cpy[j])
		{
			if (!strncmp(data->env_cpy[j], sp[i], ft_lenvar(sp[i])))
			{
				ft_printf("ptdr2\n");
				break ;
			}
			j++;
		}
		if (data->env_cpy[j])
		{
			ft_printf("ptdr\n");
			new_cpy = malloc(sizeof(char *) * data->env_len);
			j = 0;
			k = 0;
			while (data->env_cpy[j])
			{
				if (!strncmp(data->env_cpy[j], sp[i], ft_lenvar(sp[i])))
				{
					ft_printf("ptdr3\n");
					free(data->env_cpy[j]);
					ft_printf("ptdr3\n");
					j++;
				}
				ft_printf("%s\n", data->env_cpy[j]);
				new_cpy[k] = data->env_cpy[j];
				j++;
				k++;
			}
			ft_printf("ptdr3\n");
			free(data->env_cpy);
			new_cpy[++k] = NULL;
			data->env_cpy = new_cpy;
		}
		i++;
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
