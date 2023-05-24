/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/05/24 15:36:34 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	int i=0;
	char *lol;
	char *xd;
	(void)argc;
	(void)argv;
	xd = malloc(3000);
	xd = getcwd(lol, 0);
	//while (env[i])
	//	printf("%s\n", env[i++]);
	while (1)
	{
		lol = readline("\033[1;36m➜ "NAME" >\033[0m ");
		add_history(lol);
		if (!ft_strncmp(lol, "pwd", 3))
			ft_printf("%s\n", xd);
			//printf("ok\n");
	}
	return (0);
}
