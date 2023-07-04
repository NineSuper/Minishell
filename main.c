/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/28 14:22:37 by ltressen         ###   ########.fr       */
=======
/*   Updated: 2023/06/30 10:23:54 by ltressen         ###   ########.fr       */
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data				*data;
	char				*prompt;
	struct sigaction	sig;

	(void)argc;
	(void)argv;
	sig.sa_handler = ft_ctrl_c;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	data = ft_calloc(1, sizeof(t_data));
	ft_getenv(data, env);
	ft_getpwd(data);
	ft_gethome(data);
	data->term = dup(1);
	data->termo = dup(0);
	while (1)
	{
		prompt = ft_readline();
		if (!prompt)
			ft_exit(data, prompt);
		if (prompt[0])
			add_history(prompt);
		ft_parsingg(data, prompt);
		free(prompt);
	}
	free(data);
	return (0);
}
