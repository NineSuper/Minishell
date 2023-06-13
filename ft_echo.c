/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:30:03 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/12 16:59:11 by alsaez           ###   ########.fr       */
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
void	ft_echo(t_data *data, char *prompt)
{
    char	**split;
    int		i;
	int		flag;

	split = ft_split(prompt, ' ');
	if (!split[1])
		return ;
	i = ft_check_n(split);
	flag = i;
	if (!split[i])
		return ;
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
	ft_freesplit(split);
}*/
