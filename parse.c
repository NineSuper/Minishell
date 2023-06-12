/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:38:43 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/30 15:10:43 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parse(t_data * data, char *prompt, char **env)
{
	t_cmd cmd;
	char **parsed;

	parsed = ft_split(prompt, '|');
	cmd.promp = ft_split(parsed[0], ' ');
	cmd.cmd = cmd.promp[0];
	if (cmd.promp[1] && cmd.promp[1][0] == '-')
		cmd.opt = cmd.promp[1];
	ft_freesplit(parsed);

}

void	ft_parsing(t_data *data, char *prompt, char **env)
{
	t_cmd cmd;
	int	i;
	char **parsed;

	ft_parse(data, prompt, env);
	parsed = ft_split(prompt, ' ');
	if (!parsed[0])
		return ;
	i = 0;
	if (!ft_strncmp(parsed[0], "pwd", 4))
	{
		ft_getpwd(data);
		ft_printf("%s\n", data->pwd);
	}		
	else if (!ft_strncmp(parsed[0], "env", 4))
	{
		//ft_getenv(data, env);
		while (data->env_cpy[i])
			ft_printf("%s\n", data->env_cpy[i++]);
		i = 0;
	}
	else if (!ft_strncmp(parsed[0], "cd", 3))
		ft_cd(data, prompt, env);
	else if (!ft_strncmp(parsed[0], "echo", 5))
		ft_echo(data, prompt);
	else if (!ft_strncmp(parsed[0], "exit", 5))
		ft_exit(data, prompt);
	else if (!ft_strncmp(parsed[0], "export", 7))
		ft_export(data, prompt);
	else
		ft_error_cmd(parsed[0]); 
	ft_freesplit(parsed);
}

void	ft_exit(t_data *data, char *prompt)
{
	ft_printf("exit\n");
	ft_freesplit(data->env_cpy);
	free(data);
	exit(EXIT_SUCCESS);
}

void	ft_error_cmd(char *str)
{
	ft_printf("Command : %s not found. \n", str);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while(split[i])
		free(split[i++]);
	free(split);
}