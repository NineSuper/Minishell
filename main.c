/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/14 14:51:19 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argc;
	(void)argv;
	char *prompt;
	int	i;

	i = 0;
	data = ft_calloc(1, sizeof(t_data));
	ft_getenv(data, env);
	while (1)
	{
		prompt = ft_readline();
		if (prompt[0])
			add_history(prompt);
		ft_parsing(data, prompt, env);
	}
	ft_exit(data, prompt);
	return (0);
}
