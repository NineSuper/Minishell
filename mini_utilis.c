/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:18:59 by jcasades          #+#    #+#             */
/*   Updated: 2023/06/26 16:48:23 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinc(char *s1, char s2)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (strlen(s1) + 2));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = s2;
	i++;
	str[i] = '\0';
	free(s1);
	return (str);
}

static int	check_quote(char *str)
{
	while (*str)
	{
		if (*str == 34)
		{
			str++;
			while (*str && *str != 34)
				str++;
			if (!*str)
				return (0);
			str++;
		}
		if (*str == 39)
		{
			str++;
			while (*str && *str != 39)
				str++;
			if (!str)
				return (0);
			str++;
		}
		str++;
	}
	return (1);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;
	char	d;

	i = 1;
	trigger = 0;
	while (*str)
	{		
		if (*str != c)
		{
			if (*str == 34 || *str == 39)
			{
				d = *str;
				str++;
				while (*str != d)
					str++;
			}
			trigger = 0;
		}
		else if (*str == c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_neosplit(char *str, char c)
{
	int	i;
	int	j;
	int	index;
	char	d;	
	char	**split;

	if (check_quote(str) == 1)
	{
		split = malloc(((count_words(str, c) + 1) * sizeof(char *)));
		if (!str || !split)
			return (0);
		i = 0;
		j = 0;
		index = -1;
		while (i < ft_strlen(str))
		{
			if (str[i] != c && index < 0)
			{
				if (str[i] == 34 || str[i] == 39)
				{
					d = str[i++];
					while (str[i] != d)
						i++;
				}	
				index = i;
			}
			else if ((str[i] == c || i == ft_strlen(str)) && index >= 0)
			{
				split[j++] = word_dup(str, index, i);
				index = -1;
			}
			i++;
		}
		ft_printf("%s", split[0]);
		split[j] = NULL;
		return (split);
	}
	else
		return (NULL);
}
