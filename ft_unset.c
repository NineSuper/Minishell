/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:35:30 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/27 12:22:32 by tde-los-         ###   ########.fr       */
=======
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:35:30 by tde-los-          #+#    #+#             */
/*   Updated: 2023/07/03 11:13:33 by ltressen         ###   ########.fr       */
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (data->env_cpy[i])
		ft_cpy_env(data, i);
<<<<<<< HEAD
=======
	free(arg);
	return (0);
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
}

int	ft_unset(t_data *data, char *prompt)
{
	char	**split;
	int		i;

	split = ft_split(prompt, ' ');
	i = 0;
	if (!split[1])
	{
		ft_freesplit(split);
		return (printf("unset: not enough arguments\n"));
	}
	while (split[++i])
		ft_arg_unset(data, split[i]);
	ft_freesplit(split);
<<<<<<< HEAD
=======
	return (0);
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
}
