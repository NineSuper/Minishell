/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:15 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/12 14:00:01 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_ctrl_d(char *prompt)
{
	ft_printf("exit\n");
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argc;
	(void)argv;
	char *prompt;
	int	i;
	pid_t pid;
	struct sigaction sig;

	sig.sa_handler = ft_ctrl_c;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);

	i = 0;
	data = ft_calloc(1, sizeof(t_data));
	ft_getenv(data, env);
	ft_getpwd(data);
	while (1)
	{
		prompt = ft_readline();
		add_history(prompt);
		ft_parsing(data, prompt, env);
	}
	free(data);
	return (0);
}




