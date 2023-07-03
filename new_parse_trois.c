/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_trois.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:01:27 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/03 12:59:53 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_data *data, int i, int flag)
{
	int	j;

	j = 0;
	if (!ft_third_parse(data, i))
		exit(0);
	if (!data->cmd[0])
		exit(0);
	if (!ft_strncmp(data->cmd[i], "cd", 3))
		ft_cd(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "echo", 5))
		ft_echo(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "export", 7))
		ft_export(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "unset", 6))
		ft_unset(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "env", 4))
		while (data->env_cpy[j])
			ft_printf("%s\n", data->env_cpy[j++]);
	else if (!ft_strncmp(data->cmd[i], "pwd", 4))
	{
		ft_getpwd(data);
		ft_printf("%s\n", data->pwd);
	}		
	else if (!ft_strncmp(data->cmd[i], "exit", 5))
		ft_exit(data, NULL);
	else
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

void	is_builtin(t_data *data, char *cmd, int i)
{
	if (!ft_strncmp(cmd, "cd", 3))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "echo", 5))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "export", 7))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "unset", 6))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "env", 4))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "pwd", 4))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "exit", 5))
		data->builtin[i] = 1;
	else
		data->builtin[i] = 0;
}

int	ft_first_parse(t_data *data, char *prompt)
{
	int		i;
	char	**tmp;

	i = 0;
	data->cmd_full = ft_neosplit(prompt, '|');
	if (!data->cmd_full)
		return (0);
	while (data->cmd_full[i])
		i++;
	data->pipenum = i;
	data->cmd = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (data->cmd_full[i])
	{
		tmp = ft_split(data->cmd_full[i], ' ');
		if (tmp[0])
			data->cmd[i] = ft_strdup(tmp[0]);
		else
		{
			ft_freesplit(data->cmd_full);
			ft_freesplit(data->cmd);
			ft_freesplit(tmp);
			return (i);
		}
		ft_freesplit(tmp);
		i++;
	}
	return (i);
}

void	ft_second_parse(t_data *data)
{
	int	i;

	i = 0;
	data->pipes = ft_calloc(data->pipenum, sizeof(int *));
	while (i < data->pipenum - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		pipe(data->pipes[i]);
		i++;
	}
}
