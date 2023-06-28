/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:18:59 by jcasades          #+#    #+#             */
/*   Updated: 2023/06/28 13:16:27 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_opentrunk(t_data *data, int i , int j)
{
	int	k;
	int	l;
	char	*cmd;
	int	fd;

	j++;
	l = 0;
	while(data->cmd_full[i][j] == ' ' && data->cmd_full[i][j])
		j++;
	k = j;
	while(data->cmd_full[i][j] != ' ' && data->cmd_full[i][j])
		j++;
	cmd = malloc(j - k + 1);
	while(data->cmd_full[i][k] != ' ' && data->cmd_full[i][k])
	{
		cmd[l] = data->cmd_full[i][k];
		l++;
		k++;
	}
	cmd[l] = '\0';
	fd = open(cmd, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	dup2(fd, 1);
	close(fd);
	free(cmd);
	return (j);
}

int	ft_openapp(t_data *data, int i, int j)
{
	int	k;
	int	l;
	char	*cmd;
	int	fd;

	j += 2;
	l = 0;
	while(data->cmd_full[i][j] == ' ' && data->cmd_full[i][j])
		j++;
	k = j;
	while(data->cmd_full[i][j] != ' ' && data->cmd_full[i][j])
		j++;
	cmd = malloc(j - k + 1);
	while(data->cmd_full[i][k] != ' ' && data->cmd_full[i][k])
	{
		cmd[l] = data->cmd_full[i][k];
		l++;
		k++;
	}
	cmd[l] = '\0';
	fd = open(cmd, O_CREAT | O_APPEND | O_WRONLY, 0644);
	dup2(fd, 1);
	close(fd);
	free(cmd);
	return (j);
}

int	ft_input(t_data *data, int i, int j)
{
	int	k;
	int	l;
	char	*cmd;
	int	fd;

	j++;
	l = 0;
	while(data->cmd_full[i][j] == ' ' && data->cmd_full[i][j])
		j++;
	k = j;
	while(data->cmd_full[i][j] != ' ' && data->cmd_full[i][j])
		j++;
	cmd = malloc(j - k + 1);
	while(data->cmd_full[i][k] != ' ' && data->cmd_full[i][k])
	{
		cmd[l] = data->cmd_full[i][k];
		l++;
		k++;
	}
	cmd[l] = '\0';
	fd = open(cmd, O_RDONLY);
	if (fd < 0)
	{
		dup2(data->term, 1);
		close(data->term);
		ft_printf("error cpt mdr\n");
		return (0);
	}
	else
	{
		dup2(fd, 0);
		close(fd);
	}
	return (j);
}

int	ft_limit(t_data *data, int i, int j)
{
	int	k;
	int	l;
	char	*cmd;
	int	fd;
	char	*new_prompt;


	j += 2;
	l = 0;
	while(data->cmd_full[i][j] == ' ' && data->cmd_full[i][j])
		j++;
	k = j;
	while(data->cmd_full[i][j] != ' ' && data->cmd_full[i][j])
		j++;
	cmd = malloc(j - k + 1);
	while(data->cmd_full[i][k] != ' ' && data->cmd_full[i][k])
	{
		cmd[l] = data->cmd_full[i][k];
		l++;
		k++;
	}
	cmd[l] = '\0';
	if (!cmd[0])
	{
		dup2(data->term, 1);
		ft_printf("empty delimiter\n");
		return (j);
	}
	while (1)
	{
		new_prompt = readline(">");
		if (!ft_strncmp(new_prompt, cmd, ft_strlen(cmd)))
			break ;
	}
	return (j);
}