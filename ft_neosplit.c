/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_neosplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:29:48 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/04 10:29:54 by jcasades         ###   ########.fr       */
=======
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:ft_neosplit.c
/*   Created: 2023/07/04 10:29:48 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/04 14:29:27 by ltressen         ###   ########.fr       */
========
/*   Created: 2023/06/26 10:18:59 by jcasades          #+#    #+#             */
/*   Updated: 2023/07/03 15:37:19 by jcasades         ###   ########.fr       */
>>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8:mini_utilis.c
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
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
		}
		if (*str == 39)
		{
			str++;
			while (*str && *str != 39)
				str++;
			if (!str)
				return (0);
		}
		str++;
	}
	return (1);
}

static int	count_words(const char *str, char c, int i, int trigger)
{
	char	d;

	while (*str)
	{
		if ((*str != c && trigger == 0) || *str == 34 || *str == 39)
		{
			if (*str == 34 || *str == 39)
			{
				d = *str;
				str++;
				while (*str != d)
					str++;
				str++;
				if (!*str)
					return (i);
			}
			if (trigger == 0)
				i++;
			trigger = 1;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	start = -1;
	return (word);
}

char	**ft_neosplit(char *str, char c, int i, int j)
{
	int		index;
	char	d;
	char	**split;

	split = malloc(((count_words(str, c, 0, 0) + 1) * sizeof(char *)));
	index = -1;
<<<<<<< HEAD
	while ((size_t)++i <= ft_strlen(str))
=======
<<<<<<<< HEAD:ft_neosplit.c
	while ((size_t)i <= ft_strlen(str))
========
	while ((size_t)++i <= ft_strlen(str))
>>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8:mini_utilis.c
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8
	{
		if (str[i] != c && index < 0)
			index = i;
		if (str[i] == 34 || str[i] == 39)
		{
			d = str[i++];
			while (str[i] != d)
				i++;
<<<<<<< HEAD
=======
<<<<<<<< HEAD:ft_neosplit.c
		}
		else if ((str[i] == c || (size_t)i == ft_strlen(str)) && index >= 0)
		{
			split[j++] = word_dup(str, index, i);
			index = -1;
		}
		i++;
========
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8
		}
		else if ((str[i] == c
				|| (size_t)i == ft_strlen(str)) && index >= 0)
		{
			split[j++] = word_dup(str, index, i);
			index = -1;
		}
<<<<<<< HEAD
=======
>>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8:mini_utilis.c
>>>>>>> 0818ad934bc4e728a12667a9ed7a27be4d9e24d8
	}
	split[j] = 0;
	return (split);
}
