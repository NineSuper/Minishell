/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:35:09 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/03 12:59:53 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, int i)
{
	char	*cmd;

	cmd = ft_chk_cmd(data, i);
	if (cmd)
	{
		if (execve(cmd, ft_split(data->cmd_full[i], ' '), data->env_cpy) == -1)
		{
			data->errnum = errno;
			perror("Error");
			free(cmd);
			exit(0);
		}
		free(cmd);
		exit(0);
	}
	else
		exit(0);
}

int	ft_third_parse(t_data *data, int i)
{
	char	*new_cmd;
	char	*arg;
	char	*error;
	int		j;
	int		k;

	j = 0;
	k = 0;
	error = ft_itoa(data->errnum >> 8);
	new_cmd = ft_calloc(1, 1);
	while (data->cmd_full[i][j])
	{
		while (data->cmd_full[i][j] != '<' && data->cmd_full[i][j] != '>'
			&& data->cmd_full[i][j] != '\'' && data->cmd_full[i][j] != '"'
			&& data->cmd_full[i][j] != '$' && data->cmd_full[i][j] != ' '
			&& data->cmd_full[i][j])
		{
			new_cmd = ft_strjoinc(new_cmd, data->cmd_full[i][j]);
			j++;
			k++;
		}
		if (data->cmd_full[i][j] == ' ')
		{
			new_cmd = ft_strjoinc(new_cmd, ' ');
			k++;
			j++;
			while (data->cmd_full[i][j] == ' ')
				j++;
		}
		if (data->cmd_full[i][j] == '<')
		{
			if (data->cmd_full[i][j + 1] == '<')
			{
				j = ft_limit(data, i, j);
				j++;
			}
			else
			{
				j = ft_input(data, i, j);
				if (j == 0)
					return (0);
				j++;
			}
		}
		if (data->cmd_full[i][j] == '>')
		{
			if (data->cmd_full[i][j + 1] == '>')
			{
				j = ft_openapp(data, i, j);
				j++;
			}
			else
			{
				j = ft_opentrunk(data, i, j);
				j++;
			}
		}
		if (data->cmd_full[i][j] == '\'')
		{
			j++;
			while (data->cmd_full[i][j] != '\'' && data->cmd_full[i][j] != '\0')
			{
				new_cmd = ft_strjoinc(new_cmd, data->cmd_full[i][j]);
				j++;
			}
			if (data->cmd_full[i][j] == '\0')
			{
				ft_printf("error");
				exit(1);
			}
			else
				j++;
		}
		if (data->cmd_full[i][j] == '"')
		{
			j++;
			while (data->cmd_full[i][j] != '"' && data->cmd_full[i][j] != '\0')
			{
				if (data->cmd_full[i][j] == '$')
				{	
					if (data->cmd_full[i][j + 1] != '?')
					{
						arg = ft_reparg(data, i, j);
						new_cmd = ft_strjoinfree(new_cmd, arg);
						if (arg)
							free(arg);
					}
					else
						new_cmd = ft_strjoinfree(new_cmd, error);
					while (data->cmd_full[i][j] != ' '
					&& data->cmd_full[i][j] != '"')
						j++;
				}
				j++;
			}
		}
		if (data->cmd_full[i][j] == '$')
		{
			if (data->cmd_full[i][j + 1] != '?')
			{
				arg = ft_reparg(data, i, j);
				new_cmd = ft_strjoinfree(new_cmd, arg);
				if (arg)
					free(arg);
			}
			else
				new_cmd = ft_strjoinfree(new_cmd, error);
			while (data->cmd_full[i][j] != ' ' && data->cmd_full[i][j] != '\0')
				j++;
		}
	}
	free(error);
	free(data->cmd_full[i]);
	data->cmd_full[i] = ft_strdup(new_cmd);
	free(new_cmd);
	return (1);
}
