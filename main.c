/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/05/24 14:32:45 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	int i=0;
	char *lol;
	(void)argc;
	(void)argv;
	while (env[i])
		printf("%s\n", env[i++]);
	while (1)
	{
		lol = readline("\033[1;36m➜ Minisheel >\033[0m ");
		add_history(lol);
	}
	return (0);
}
