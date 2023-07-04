/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:57:41 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/03 17:58:41 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipes[i])
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

pid_t	ft_piping(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
			dup2(data->pipes[i][1], 1);
		else if (i == data->pipenum - 1)
			dup2(data->pipes[i - 1][0], 0);
		else
		{
			dup2(data->pipes[i - 1][0], 0);
			dup2(data->pipes[i][1], 1);
		}
		close_pipes(data);
		ft_exec(data, i, 1);
	}
	return (pid);
}

void	single_cmd(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_exec(data, 0, 1);
	waitpid(-1, &data->errnum, 0);
}

int	ft_no_built(char *str)
{
	if (((!ft_strncmp(str, "cd", 3)
				|| !ft_strncmp(str, "echo", 5)
				|| !ft_strncmp(str, "export", 7)
				|| !ft_strncmp(str, "unset", 6)
				|| !ft_strncmp(str, "env", 4)
				|| !ft_strncmp(str, "pwd", 4))))
		return (1);
	return (0);
}

void	ft_go_pipe(t_data *data, int i)
{
	while (data->cmd_full[i])
	{
		ft_piping(data, i);
		i++;
	}
	close_pipes(data);
	i = 0;
	while (i < data->pipenum)
	{
		waitpid(-1, &data->errnum, 0);
		i++;
	}
	ft_freesplit((char **)data->pipes);
}

void	ft_parsingg(t_data *data, char *prompt)
{
	if (!ft_first_parse(data, prompt))
		return ;
	if (data->pipenum > 1)
		ft_second_parse(data);
	if (data->pipenum == 1 && !ft_strncmp(data->cmd[0], "exit", 5))
		ft_exit(data, prompt);
	else if (data->pipenum == 1 && (ft_no_built(data->cmd[0])))
		ft_exec(data, 0, 0);
	else if (data->pipenum == 1)
		single_cmd(data);
	else
		ft_go_pipe(data, 0);
	dup2(data->term, 1);
	dup2(data->termo, 0);
	ft_freesplit(data->cmd_full);
	ft_freesplit(data->cmd);
}

char	*ft_chk_cmd(t_data *data, int i, int j)
{
	char	**spt;
	char	*new_cmd;
	char	*temp;

	if (data->cmd_full[i][j] == '.' || data->cmd_full[i][j] == '/')
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
