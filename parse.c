/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:38:43 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/12 13:59:02 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_data *data, char *prompt, char **env)
{
	int	i;
	char **parsed;
	pid_t pid;

	parsed = ft_split(prompt, ' ');
	if (!parsed[0])
		return ;
	i = 0;
	if (!ft_strncmp(parsed[0], "pwd", 4))
	{
		//ft_getpwd(data);
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
	if (is_exec(parsed))
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(parsed[0], parsed, data->env_cpy) == -1)
			{
					ft_printf("%d %s\n", errno, strerror(errno));
			}
		}
	}
	ft_freesplit(parsed);
}

int	is_exec(char **parsed)
{
	int	flag;

	flag = 0;
	if (parsed[0][0] == '.' && parsed[0][1] == '/')
		flag = 1;
	else
		flag = 0;
	return (flag);
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
	while (split[i])
		free(split[i++]);
	free(split);
}
