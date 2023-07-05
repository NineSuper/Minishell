/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trolon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:56:52 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/04 12:11:48 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_third_parse(t_data *data, int i, int j)
{
	char	*new_cmd;
	char	*arg;

	new_cmd = ft_calloc(1, 1);
	while (data->cmd_full[i][j])
	{
		if (data->cmd_full[i][j] == ' ' && j++ )
		{
			new_cmd = ft_strjoinc(new_cmd, ' ');
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
			while (data->cmd_full[i][j] != '\'' && data->cmd_full[i][j] != '\0')
				new_cmd = ft_strjoinc(new_cmd, data->cmd_full[i][j++]);
			j++;
		}
		else if (data->cmd_full[i][j] == '"' && j++)
		{
			while (data->cmd_full[i][j] != '"' && data->cmd_full[i][j] != '\0')
			{
				if (data->cmd_full[i][j] == '$' && data->cmd_full[i][j + 1] != '?')
				{	
					arg = ft_reparg(data, i, j);
					new_cmd = ft_strjoin(new_cmd, arg);
					if (arg)
						free(arg);
				}
				else if (data->cmd_full[i][j] == '$')
					new_cmd = ft_strjoin(new_cmd,
							ft_itoa(data->errnum >> 8));
				while (data->cmd_full[i][j] != ' '
				&& data->cmd_full[i][j] != '"')
					j++;
			}
			j++;
		}
		else if (data->cmd_full[i][j] == '$')
		{
			if (data->cmd_full[i][j + 1] != '?')
			{
				arg = ft_reparg(data, i, j);
				new_cmd = ft_strjoin(new_cmd, arg);
				if (arg)
					free(arg);
			}
			else
				new_cmd = ft_strjoin(new_cmd, ft_itoa(data->errnum >> 8));
			while (data->cmd_full[i][j] != ' ' && data->cmd_full[i][j] != '\0')
				j++;
		}
		else 
			new_cmd = ft_strjoinc(new_cmd, data->cmd_full[i][j++]);
	}
	free(data->cmd_full[i]);
	data->cmd_full[i] = ft_strdup(new_cmd);
	free(new_cmd);
	return (1);
}
