/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/05/24 16:10:57 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argc;
	(void)argv;
	char *prompt;

	data = ft_calloc(1, sizeof(t_data));
	while (1)
	{
		prompt = readline("\033[1;36m➜ "NAME" >\033[0m ");
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
