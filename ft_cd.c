/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:22 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:09 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data, char *prompt, char **env)
{
	char	**parse;

	parse = ft_split(prompt, ' ');
	ft_gethome(data);
	ft_getpwd(data);
	if (!ft_strncmp(parse[0], "cd", 3));
	{
		if (parse[1] && parse[1][0] != '~')
		{
			if (chdir(parse[1]) == -1)
				ft_printf("cd: no such file or directory: %s\n", parse[1]);
		}
		else
		{
			chdir(data->home);
			if (parse[1])
			{
				if (parse[1][1] == '\0')
					return ;
				chdir(data->home);
				parse[1]++;
				parse[1]++;
				if (chdir(parse[1]) == -1)
				{
					ft_printf("cd: no such file or directory: %s\n", parse[1]);
					chdir(data->pwd);
				}
			}
		}
	}
}
