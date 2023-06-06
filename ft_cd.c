/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:22 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/30 10:21:42 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data, char *prompt, char **env)
{
	char	**parse;

	parse = ft_split(prompt, ' ');
	if (!ft_strncmp(parse[0], "cd", 3))
	{
		if (parse[1] && parse[1][0] != '~')
		{
			if (chdir(parse[1]) == -1)
				ft_printf("cd: no such file or directory: %s\n", parse[1]);
		}
		else
		{
			ft_gethome(data);
			chdir(data->home);
			if (parse[1])
				if (parse[1][1] == '/')
				{
					parse[1]++;
					parse[1]++;
					if (chdir(parse[1]) == -1)
						ft_printf("cd: no such file or directory: %s\n", parse[1]);
				}
		}
	}
}
