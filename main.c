/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/21 12:04:30 by ltressen         ###   ########.fr       */
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
	struct sigaction sig;

	sig.sa_handler = ft_ctrl_c;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);

	i = 0;
	data = ft_calloc(1, sizeof(t_data));
	ft_getenv(data, env);
	ft_printf("%d\n", getpid());
	while (1)
	{
		prompt = ft_readline();
		if (prompt[0])
			add_history(prompt);
		ft_parsingg(data, prompt);
		free(prompt);
	}
	free(data);
	return (0);
}
