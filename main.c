/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/05/24 16:06:09 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argc;
	(void)argv;
	char *lol;

	
	data = ft_calloc(1, sizeof(t_data));
	while (1)
	{
		lol = readline("\033[1;36m➜ "NAME" >\033[0m ");
		add_history(lol);
		if (!ft_strncmp(lol, "pwd", 3))
		{
			ft_getpwd(data);
			ft_printf("%s\n", data->pwd);
		}
	}
	free(data);
	return (0);
}
