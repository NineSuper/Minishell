/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:30:03 by tde-los-          #+#    #+#             */
/*   Updated: 2023/07/06 18:45:09 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_check_n(char *prompt, int i)
// {
// 	while (prompt[i] == 'n')
// 		i++;
// 	while (prompt[i] == ' ')
// 		i++;
// 	if (!(prompt[i] == '-' && prompt[i + 1] == 'n'))
// 		return (i);
// 	else
// 		return (ft_check_n(prompt, i + 1));
// }

// int	ft_check_n(char *tab)
// {
// 	int	i;

// 	i = 5;
// 	while (tab[i])
// 	{
// 		if (tab[i] == '-')
// 		{
// 			if (tab[i + 1] == 'n')
// 				i++;
// 			while (tab[i] == 'n' && tab[i])
// 				i++;
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	ft_check_n(char **tab)
{
	int	i;
	int	j;

	i = 1;
	while (tab[i])
	{
		if (tab[i][0] != '-')
			return (i);
		j = 1;
		while (tab[i][j])
		{
			if (tab[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
// char	*ft_new_prompt_a(char *prompt)
// {
// 	int	j;
// 	char	*new_prompt;
// 	int	trigger;

// 	j = 0;
// 	trigger = 0;
// 	new_prompt = ft_calloc(1, 1);
// 	while (prompt[j] != '\a' && prompt[j])
// 		j++;
// 	while (prompt[j])
// 	{
// 		if (prompt[j] == '\a' && trigger == 0)
// 		{
// 			trigger = 1;
// 			j++;
// 		}	
// 		if (prompt[j] == '\a' && trigger == 1)
// 		{
// 			j++;
// 			trigger = 0;
// 		}
// 		new_prompt = ft_strjoinc(new_prompt, prompt[j]);
// 		if (prompt[j] == ' ' && prompt[j + 1] != ' ' && prompt[j + 1])
// 			new_prompt = ft_strjoinc(new_prompt, prompt[j]);
// 		j++;
// 	}
// 	if (trigger == 0)
// 		return (new_prompt);	
// 	return (NULL);
// }

// char	*ft_new_prompt(char *prompt)
// {
// 	int	i;
// 	char	*new_prompt;

// 	i = 0;
// 	new_prompt = ft_calloc(1, 1);
// 	while (prompt[i] != ' ' && prompt[i])
// 		i++;
// 	while (prompt[i] == ' ' && prompt[i])
// 		i++;
// 	while (prompt[i])
// 	{
// 		new_prompt = ft_strjoinc(new_prompt, prompt[i]);
// 		i++;
// 	}
// 	return (new_prompt);
// }
void	ft_echoing(char *str, int flag)
{
	int	i;
	char	*res;

	i = 0;
	if (str[i] == '\a')
	{
		i++;
		while (str[i] != '\a' && str[i])
			i++;
		res = malloc(i + 1);
		ft_strlcpy(res, str + 1, i);
		if (flag == 0)
			ft_printf("%s ", res);
		if (flag == 1)
			ft_printf("%s", res);
		return ;
	}
	if (flag == 0)
		ft_printf("%s ", str);
	if (flag == 1)
		ft_printf("%s", str);
}

int	ft_echo(t_data *data, char *prompt)
{
	char		**split;
	int			i;
	int			flag;

	(void)data;
	split = ft_neosplit(prompt, ' ', 0, 0);
	if (!split[1])
		return (ft_freesplit(split), ft_printf("\n"));
	i = ft_check_n(split);
	flag = i;
	if (!split[i])
		return (ft_freesplit(split), 0);
	while (split[i])
	{
		if (split[i + 1])
			ft_echoing(split[i], 0);
		else
			ft_echoing(split[i], 1);
		i++;
	}
	if (flag < 2)
		ft_printf("\n");
	return (ft_freesplit(split), 0);
}

// int	check_bckslh_a(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == 7)
// 		{
// 			str++;
// 			while (*str && *str != 7)
// 				str++;
// 			if (!*str)
// 				return (0);
// 		}
// 		str++;
// 	}
// 	return (1);
// }

// int	ft_echo(t_data *data, char *prompt)
// {
// 	char	*new_prompt;

// 	(void)data;
// 	while (*prompt == ' ')
// 		prompt++;
// 	ft_printf("%s", prompt);
// 	if (ft_check_n(prompt) && check_bckslh_a(prompt) == 1) // cas ou -n et quotes
// 	{
// 		ft_printf("ici1\n");
// 		new_prompt = ft_new_prompt_a(prompt);
// 		ft_printf("%s", new_prompt);
// 		free(new_prompt);
// 	}
// 	else if (ft_check_n(prompt) && check_bckslh_a(prompt) == 1)
// 	{
// 		ft_printf("ici2\n");
// 		new_prompt = ft_new_prompt(prompt);
// 		ft_printf("%s", new_prompt);
// 		free(new_prompt);
// 	}
// 	else if (!ft_check_n(prompt) && check_bckslh_a(prompt) == 1)
// 	{
// 		ft_printf("ici3\n");
// 		new_prompt = ft_new_prompt_a(prompt);
// 		ft_printf("%s\n", new_prompt);
// 		free(new_prompt);
// 	}
// 	else
// 	{
// 		ft_printf("ici4\n");
// 		new_prompt = ft_new_prompt(prompt);
// 		ft_printf("%s\n", new_prompt);
// 		free(new_prompt);
// 	}
// 	data->errnum = 0;
// 	return (0);
// }
