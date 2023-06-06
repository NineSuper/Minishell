/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:38:43 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/06 16:11:42 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_data *data, char *prompt, char **env)
{
	int	i;
	char **parsed;

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
		//ft_getenv(data, env);
		while (data->env_cpy[i])
			ft_printf("%s\n", data->env_cpy[i++]);
		i = 0;
	}
	if (!ft_strncmp(parsed[0], "cd", 3))
		ft_cd(data, prompt, env);
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
	ft_freesplit(data->env_cpy);
	free(data);
	exit(EXIT_SUCCESS);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while(split[i])
		free(split[i++]);
	free(split);
}

void	ft_echo(t_data *data, char *prompt)
{
	int	i;
	int	j;
	char **split;
	int	n_flag;

	n_flag = 0;
	i = 1;
	split = ft_split(prompt, ' ');
	while (!ft_strncmp(split[i], "-n", 3))
	{
		n_flag = 26;
		i++;
	}
	while (split[i])
	{
		if (!split[i + 1])
		{
			ft_printf("%s", split[i]);
			if (n_flag)
				ft_printf("\033[47m\e[1;30m%%\033[m");
			ft_printf("\n");
		}
		else
			ft_printf("%s ", split[i]);
		i++;
	}
	ft_freesplit(split);
}
