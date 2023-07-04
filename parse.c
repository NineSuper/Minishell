/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:38:43 by ltressen          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/28 13:48:30 by ltressen         ###   ########.fr       */
=======
/*   Updated: 2023/07/03 13:12:25 by ltressen         ###   ########.fr       */
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_data *data, char *prompt, char **env)
{
	int		i;
	char	**parsed;

	(void)env;
	parsed = ft_split(prompt, ' ');
	if (!parsed[0])
		return ;
	i = 0;
	if (!ft_strncmp(parsed[0], "pwd", 4))
	{
		ft_getpwd(data);
		ft_printf("%s\n", data->pwd);
	}		
	if (!ft_strncmp(parsed[0], "env", 4))
	{
		while (data->env_cpy[i])
			ft_printf("%s\n", data->env_cpy[i++]);
		i = 0;
	}
	if (!ft_strncmp(parsed[0], "cd", 3))
		ft_cd(data, prompt);
	if (!ft_strncmp(parsed[0], "echo", 5))
		ft_echo(data, prompt);
	if (!ft_strncmp(parsed[0], "exit", 5))
		ft_exit(data, prompt);
	if (!ft_strncmp(parsed[0], "export", 7))
		ft_export(data, prompt);
	if (!ft_strncmp(parsed[0], "unset", 6))
		ft_unset(data, prompt);
	ft_freesplit(parsed);
}

void	ft_exit(t_data *data, char *prompt)
{
	char	**sp;
	int	exit_code;

	exit_code = 0;
	if (prompt)
	{	
		sp = ft_split(data->cmd_full[0], ' ');
		if (sp[1])
			exit_code = ft_atoi(sp[1]);
		free(prompt);
		ft_freesplit(sp);
	}
	else
	{
		free(data->home);
		free(data->pwd);
		free(data->path);
		ft_freesplit(data->env_cpy);
		free(data);
		exit(exit_code);
	}
	free(data->home);
	free(data->path);
	ft_freesplit(data->env_cpy);
	ft_freesplit(data->cmd);
	ft_freesplit(data->cmd_full);
	free(data->pipes);
	free(data->pwd);
	free(data);

	exit(exit_code);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}
