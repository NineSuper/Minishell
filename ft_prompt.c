/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:52:22 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/21 15:23:17 by ltressen         ###   ########.fr       */
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
	//name = ft_calloc(1, sizeof(char));
	name = ft_strjoin(NAME, "\033[1;32m[");
	temp = getcwd(NULL, 0);
	split = ft_split(temp, '/');
	while (split[i])
		i++;
	i--;
	if (i == -1)
	{
		ft_freesplit(split);
		split = malloc(sizeof(char *) * 2);
		split[0] = ft_strdup("/");
		split[1] = NULL;
		i++;
	}
	free(temp);
	temp = ft_strdup(name);
	free(name);
	name = ft_strjoin(temp, split[i]);
	free(temp);
	temp = ft_strdup(name);
	free(name);
	name = ft_strjoin(temp, "]\033[1;36m > \033[0m");
	prompt = readline(name);
	ft_freesplit(split);
	free(temp);
	free(name);
	return (prompt);
}
