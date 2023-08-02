/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:22 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/26 15:35:42 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo lorsqu'il y'a plus la valeur PWD / OLDPWD les rajouter a la fin de ENV

void	ft_check_pwd(t_data *data, char *str)
{
	int		j;

	j = 0;
	while (data->env_cpy[j])
	{
		if (!strncmp(data->env_cpy[j], str, ft_lenvar(str) + 1))
		{
			free(data->env_cpy[j]);
			data->env_cpy[j] = ft_strdup(str);
			break ;
		}
		j++;
	}
	if (!data->env_cpy[j])
		ft_new_export(data, str);
	free(str);
}

void	ft_changepwd(t_data *data, char *old_pwd)
{
	char	*str;
	char	*str2;
	int		i;

	i = -1;
	ft_getpwd(data);
	str = ft_strjoin("PWD=", data->pwd);
	str2 = ft_strjoin("OLDPWD=", old_pwd);
	while (data->env_cpy[++i])
	{
		if (!ft_strncmp(data->env_cpy[i], "PWD", 3))
		{
			free(data->env_cpy[i]);
			data->env_cpy[i] = ft_strdup(str);
		}
		if (!ft_strncmp(data->env_cpy[i], "OLDPWD", 6))
		{
			free(data->env_cpy[i]);
			data->env_cpy[i] = ft_strdup(str2);
		}
	}
	ft_check_pwd(data, str);
	ft_check_pwd(data, str2);
}

void	ft_arg_cd(t_data *data, char *arg, char *pwd_copy)
{
	if (arg[0] == '~' && arg[1] == '~')
	{
		ft_printf("cd: no such file or directory: %s\n", arg);
		return ;
	}
	else
	{
		chdir(data->home);
		if (chdir(arg + 2) == -1)
		{
			ft_printf("cd: no such file or directory: %s\n", arg);
			chdir(pwd_copy);
			return ;
		}
	}
}

static void	ft_go_home(t_data *data, char **parse, char *pwd_cpy)
{
	chdir(data->home);
	ft_changepwd(data, pwd_cpy);
	free(pwd_cpy);
	ft_freesplit(parse);
	return ;
}

void	ft_cd(t_data *data, char *prompt)
{
	char	**parse;
	char	*pwd_cpy;

	parse = ft_split(prompt, ' ');
	ft_getpwd(data);
	pwd_cpy = ft_strdup(data->pwd);
	if (!parse[1])
		return (ft_go_home(data, parse, pwd_cpy));
	else if (parse[2])
	{
		ft_printf("cd: too many arguments\n");
		data->errnum = 1;
	}
	if (parse[1][0] == '~' && parse[1][1] == '\0')
		chdir(data->home);
	else if (parse[1][0] == '~' && parse[1][1] != '\0')
		ft_arg_cd(data, parse[1], pwd_cpy);
	else if (chdir(parse[1]) == -1)
	{
		ft_printf("cd: no such file or directory: %s\n", parse[1]);
		data->errnum = 1;
	}
	ft_changepwd(data, pwd_cpy);
	free(pwd_cpy);
	ft_freesplit(parse);
}
