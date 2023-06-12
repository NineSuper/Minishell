/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:16:24 by jcasades          #+#    #+#             */
/*   Updated: 2023/06/12 13:45:33 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first_parse(t_data *data, char *prompt)
{
	int	i;
	int	j;
	char	**tmp;

	i = 0;
	data->cmd_full=ft_split(prompt, '|');
	while (data->cmd_full[i])
		i++;
	data->pipenum = i;
	data->cmd = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (data->cmd_full[i])
	{
		tmp = ft_split(data->cmd_full[i], ' ');
		data->cmd[i] = ft_strdup(tmp[0]);
		j = 0;
		while (tmp[j])
		{
			free(tmp[j]);
			j++;
		}
		free (tmp);
		i++;
	}
}

void	ft_second_parse(t_data *data)
{

	data->pipes = malloc((sizeof int *) * 2);
	data->pipes[0] = malloc ((sizeof int) * 2);
	pipe(data->pipes[0]);
	data->pipes[1] = malloc ((sizeof int) * 2);
	pipe(data->pipes[1]);
}

char	*ft_chk_cmd(t_data,

void	ft_exec(t_data *data, int i)
{
	if (data->cmd[i] == "cd")
		ft_cd(
	else if (data->cmd[i] == "echo")
	else if (data->cmd[i] == "export")
	else if (data->cmd[i] == "unset")
	else if (data->cmd[i] == "env")
	else if (data->cmd[i] == "pwd")
	else
}
void	ft_piping(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
		{
			dup2(data->fd1, 0);
			dup2(data->pipes[i][0], 1);
		}
		else if (i == data->pipenum - 1) 
		{
			dup2(data->pipes[i][1], 0);
			dup2(data->fd2, 1);
		}
		else
		{
			dup2(data->pipes[i % 2][1], 0);
			dup2(data->pipes[(i + 1) % 2][0], 1);
		}
		ft_exec(data, i);	
	}
}

void	ft_parsingg(t_data *data, char *prompt)
{
	int	i;
	int	fd;

	i = 0;
	ft_first_parse(data, prompt);
	ft_second_parse(data);
	data->fd1 = open(".tmp1", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	data->fd2 = open(".tmp2", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	while (data->cmd_full[i])
	{
		ft_piping(data, i);
		i++;
	}
}
