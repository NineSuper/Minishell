/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:44:53 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/25 12:42:09 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_ff;

void	single_cmd(t_data *data)
{
	pid_t	pid;

	pid = fork();
	g_ff = 1;
	if (pid == 0)
		ft_exec(data, 0, 1);
	waitpid(-1, &data->errnum, 0);
	g_ff = 0;
}

char	*ft_chk_cmd(t_data *data, int i, int j)
{
	char	**spt;
	char	*new_cmd;
	char	*temp;

	if (data->full[i][j] == '.' || data->full[i][j] == '/')
		return (data->cmd[i]);
	spt = ft_split(data->path, ':');
	j = -1;
	while (spt[++j])
	{
		new_cmd = ft_strjoin(spt[j], "/");
		temp = ft_strjoin(new_cmd, data->cmd[i]);
		free(new_cmd);
		if (access(temp, 0) == 0)
		{
			ft_freesplit(spt);
			return (temp);
		}
		free(temp);
	}
	ft_freesplit(spt);
	dup2(data->term, 1);
	return (NULL);
}

static void	ft_suite(t_data *data, int i, int flag)
{
	int	j;

	j = 0;
	if (!ft_strncmp(data->cmd[i], "env", 4))
		while (data->env_cpy[j])
			ft_printf("%s\n", data->env_cpy[j++]);
	else if (!ft_strncmp(data->cmd[i], "pwd", 4))
	{
		ft_getpwd(data);
		ft_printf("%s\n", data->pwd);
	}
	else if (!ft_strncmp(data->cmd[i], "exit", 5))
		ft_exit(data, NULL);
	else if (!ft_no_built(data->cmd[i]))
		ft_execve(data, i);
	if ((!ft_strncmp(data->cmd[i], "cd", 3)
			|| !ft_strncmp(data->cmd[i], "echo", 5)
			|| !ft_strncmp(data->cmd[i], "export", 7)
			|| !ft_strncmp(data->cmd[i], "unset", 6)
			|| !ft_strncmp(data->cmd[i], "env", 4)
			|| !ft_strncmp(data->cmd[i], "pwd", 4))
		&& flag == 1)
		exit(0);
}

void	ft_exec(t_data *data, int i, int flag)
{
	data->new_cmd = ft_calloc(1, 1);
	if (!ft_third_parse(data, i, 0))
		exit(1);
		//ft_exit(data, data->full[i]);
	if (!data->cmd[0])
		exit(1);
		//ft_exit(data, data->full[i]);
	if (!ft_strncmp(data->cmd[i], "cd", 3))
		ft_cd(data, data->full[i]);
	else if (!ft_strncmp(data->cmd[i], "echo", 5))
		ft_echo(data, data->full[i]);
	else if (!ft_strncmp(data->cmd[i], "export", 7))
		ft_export(data, data->full[i]);
	else if (!ft_strncmp(data->cmd[i], "unset", 6))
		ft_unset(data, data->full[i]);
	ft_suite(data, i, flag);
}

void	ft_checkpwd(t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (data->env_exec[0])
		ft_freesplit(data->env_exec);
	while (data->env_cpy[i])
	{
		if (!ft_strncmp(data->env_cpy[i], "PWD=", 4))
			flag = 0;
		i++;
	}
	data->env_exec = malloc(sizeof(char *) * (i + flag));
	i = 0;
	while (data->env_cpy[i])
	{
		data->env_exec[i] = ft_strdup(data->env_cpy[i]);
		i++;
	}
	if (flag == 1)
		data->env_exec[i] = ft_strdup(data->pwd);
}

void	ft_execve(t_data *data, int i)
{
	char	*cmd;

	cmd = ft_chk_cmd(data, i, 0);
	if (cmd)
	{
		//ft_checkpwd(data);
		if (execve(cmd, ft_split(data->full[i], ' '), data->env_cpy) == -1)
		{
			data->errnum = errno >> 8;
			free(cmd);
			exit(data->errnum);
		}
		data->errnum = 0;
		free(cmd);
		exit(data->errnum);
	}
	else
	{
		data->errnum = 127;
		ft_printf("%s: command not found\n", data->cmd[i]);
		exit(127);
	}
}
