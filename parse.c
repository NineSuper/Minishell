/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:38:43 by ltressen          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/04 10:44:20 by jcasades         ###   ########.fr       */
=======
/*   Updated: 2023/07/04 14:32:06 by ltressen         ###   ########.fr       */
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_first_parse(t_data *data, char *prompt)
{
	int		i;
	char	**tmp;

	i = 0;
	if (prompt[0])
	{
		if (check_quote(prompt) == 1)
<<<<<<< HEAD
			data->cmd_full = ft_neosplit(prompt, '|', -1, 0);
	}
	if (!data->cmd_full)
=======
			data->cmd_full = ft_neosplit(prompt, '|', 0, 0);
	}
	if (prompt[0] == '\0')
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8
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
