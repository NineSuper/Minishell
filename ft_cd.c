/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:22 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/08 12:34:46 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_changepwd(t_data *data, char *old_pwd)
{
	char	*str;
	int		i;

	i = 0;
	while (ft_strncmp(data->env_cpy[i], "PWD", 3))
		i++;
	ft_getpwd(data);
	str = ft_strjoin("PWD=", data->pwd);
	data->env_cpy[i] = ft_strdup(str);
	i = 0;
	while (ft_strncmp(data->env_cpy[i], "OLDPWD", 6))
		i++;
	str = ft_strjoin("OLDPWD=", old_pwd);
	data->env_cpy[i] = ft_strdup(str);
	free(old_pwd);
	free(str);
}

void	ft_cd(t_data *data, char *prompt, char **env)
{
	char	**parse;
	char	*pwd_copy;

	parse = ft_split(prompt, ' ');
	ft_gethome(data);
	ft_getpwd(data);
	pwd_copy = ft_strdup(data->pwd);
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
				{
					ft_changepwd(data, pwd_copy);
					return ;
				}
				chdir(data->home);
				parse[1] += 2;
				if (chdir(parse[1]) == -1)
				{
					ft_printf("cd: no such file or directory: %s\n", parse[1] - 2);
					chdir(data->pwd);
				}
			}
		}
	}
	ft_changepwd(data, pwd_copy);
}
