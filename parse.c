/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:38:43 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/29 15:48:26 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_data *data, char *prompt, char **env)
{
	int	i;
	char **parsed;

	parsed = ft_split(prompt, ' ');
	i = 0;
	if (!ft_strncmp(parsed[0], "pwd", 4))
	{
		ft_getpwd(data);
		ft_printf("%s\n", data->pwd);
	}		
	if (!ft_strncmp(parsed[0], "env", 4))
	{
		//ft_getenv(data, env);
		while (data->env_cpy[i])
			ft_printf("%s\n", data->env_cpy[i++]);
		i = 0;
	}
	if (!ft_strncmp(parsed[0], "echo", 5))
		ft_echo(data, prompt);
}

void	ft_echo(t_data *data, char *prompt)
{
	int	i;
	int	j;
	char **split;
	char *to_print;
	int	n_flag;

	n_flag = 0;
	i = 1;
	j = 0;
	split = ft_split(prompt, ' ');
	while (split[i])
	{
		if (!ft_strncmp(split[i], "-n", 3))
			n_flag = 1;
		else
			to_print = ft_strjoin(to_print, split[i]);
		i++;
	}
	ft_printf("%s\n", to_print);
}