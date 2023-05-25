/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/05/25 10:34:52 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(t_data *data)
{
	char	**split;
	char	*prompt;
	char	*name;
	int		i;

	i = 0;
	name = ft_calloc(1, sizeof(char));
	name = ft_strjoin(NAME, "\033[1;32m[");
	ft_getpwd(data);
	split = ft_split(data->pwd, '/');
	while (split[i])
		i++;
	i--;
	name = ft_strjoin(name, split[i]);
	name = ft_strjoin(name, "]\033[1;36m > \033[0m");
	prompt = readline(name);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	free(data->pwd);
	return (prompt);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argc;
	(void)argv;
	char *prompt;

	data = ft_calloc(1, sizeof(t_data));
	while (1)
	{
		prompt = ft_readline(data);
		add_history(prompt);
		if (!ft_strncmp(prompt, "pwd", 4))
		{
			ft_getpwd(data);
			ft_printf("%s\n", data->pwd);
		}
	}
	free(data);
	return (0);
}
