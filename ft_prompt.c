/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:52:22 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/07 09:59:52 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(void)
{
	char	**split;
	char	*prompt;
	char	*name;
	char	*temp;
	int		i;

	i = 0;
	name = ft_calloc(1, sizeof(char));
	name = ft_strjoin(NAME, "\033[1;32m[");
	temp = getcwd(NULL, 0);
	split = ft_split(temp, '/');
	while (split[i])
		i++;
	i--;
	name = ft_strjoin(name, split[i]);
	name = ft_strjoin(name, "]\033[1;36m > \033[0m");
	prompt = readline(name);
    ft_freesplit(split);
	free(temp);
	return (prompt);
}
