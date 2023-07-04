/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:30:03 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/30 10:25:59 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_n(char **tab)
{
	int	i;
	int	j;

	i = 1;
	while (tab[i])
	{
		if (tab[i][0] != '-')
			return (i);
		j = 1;
		while (tab[i][j])
		{
			if (tab[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
/*
todo echo $? = 0 si la commande passe est bonne sinon 127 si error
*/

// int	ft_arg_echo(t_data *data, char *arg)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	j = 0;
// 	while (arg[i] == '$')
// 		i++;
// 	if (i != 1)
// 		return (ft_printf("%s ", arg + i));
// 	arg++;
// 	arg = ft_strjoin(arg, "=");
// 	while (data->env_cpy[i])
// 	{
// 		if (!ft_strncmp(data->env_cpy[i], arg, ft_strlen(arg)))
// 		{
// 			while (data->env_cpy[i][j] != '=')
// 				j++;
// 			ft_printf("%s ", data->env_cpy[i] + j + 1);
// 		}
// 		i++;
// 	}
// }

int	ft_echo(t_data *data, char *prompt)
{
	char		**split;
	int			i;
	int			flag;

	(void)data;
	split = ft_split(prompt, ' ');
	if (!split[1])
		return (ft_freesplit(split), ft_printf("\n"));
	i = ft_check_n(split);
	flag = i;
	if (!split[i])
		return (ft_freesplit(split), 0);
	while (split[i])
	{
		if (split[i + 1])
			ft_printf("%s ", split[i]);
		else
			ft_printf("%s", split[i]);
		i++;
	}
	if (flag < 2)
		ft_printf("\n");
	return (ft_freesplit(split), 0);
}
