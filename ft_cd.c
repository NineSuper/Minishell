/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:22 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/30 09:59:20 by ltressen         ###   ########.fr       */
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
		}
	}
	free(parse);
}