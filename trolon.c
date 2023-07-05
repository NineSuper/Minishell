/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trolon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:56:52 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/04 11:26:10 by jcasades         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tp_quote(t_data *data, int i, int j)
{
	while (data->cmd_full[i][j] != '"' && data->cmd_full[i][j] != '\0')
	{
		if (data->cmd_full[i][j] == '$')
		{
			if (data->cmd_full[i][j + 1] != '?')
			{	
				data->arg = ft_reparg(data, i, j);
				data->new_cmd = ft_strjoinfree(data->new_cmd, data->arg);
				if (data->arg)
					free(data->arg);
			}
			else
				data->new_cmd = ft_strjoinfree(data->new_cmd,
						ft_itoa(data->errnum >> 8));
			while (data->cmd_full[i][j] != ' '
			&& data->cmd_full[i][j] != '"')
				j++;
		}
		data->new_cmd = ft_strjoinc(data->new_cmd, data->cmd_full[i][j]);
		j++;
	}
	return (j + 1);
}

static int	ft_tp_dollar(t_data *data, int i, int j)
{
	if (data->cmd_full[i][j + 1] != '?')
	{
		data->arg = ft_reparg(data, i, j);
		data->new_cmd = ft_strjoinfree(data->new_cmd, data->arg);
		if (data->arg)
			free(data->arg);
	}
	else
		data->new_cmd = ft_strjoinfree(data->new_cmd,
				ft_itoa(data->errnum >> 8));
	while (data->cmd_full[i][j] != ' ' && data->cmd_full[i][j] != '"'
			&& data->cmd_full[i][j] != '\0')
		j++;
	return (j);
}

int	ft_third_parse(t_data *data, int i, int j)
{
	data->new_cmd = ft_calloc(1, 1);
	while (data->cmd_full[i][j])
	{
		if (data->cmd_full[i][j] == ' ' && j++)
		{
			data->new_cmd = ft_strjoinc(data->new_cmd, ' ');
			while (data->cmd_full[i][j] == ' ')
				j++;
		}
		else if (data->cmd_full[i][j] == '<' && j++)
		{
			if (data->cmd_full[i][j] == '<')
				j = ft_limit(data, i, j + 1, 0) + 1;
			else
			{
				j = ft_input(data, i, j, 0) + 1;
				if (j == 1)
					return (0);
			}
		}
		else if (data->cmd_full[i][j] == '>' && j++)
		{
			if (data->cmd_full[i][j] == '>')
				j = ft_openapp(data, i, j);
			else
				j = ft_opentrunk(data, i, j) + 1;
		}
		else if (data->cmd_full[i][j] == '\'' && j++)
		{
			while (data->cmd_full[i][j] != '\''
					&& data->cmd_full[i][j] != '\0')
				data->new_cmd = ft_strjoinc(data->new_cmd,
						data->cmd_full[i][j++]);
			j++;
		}
		else if (data->cmd_full[i][j] == '"' && j++)
			j = ft_tp_quote(data, i, j);
		else if (data->cmd_full[i][j] == '$')
			j = ft_tp_dollar(data, i, j);
		else
			data->new_cmd = ft_strjoinc(data->new_cmd, data->cmd_full[i][j++]);
	}
	free(data->cmd_full[i]);
	data->cmd_full[i] = ft_strdup(data->new_cmd);
	free(data->new_cmd);
	return (1);
}
