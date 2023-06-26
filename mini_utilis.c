/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:18:59 by jcasades          #+#    #+#             */
/*   Updated: 2023/06/26 16:23:12 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strjoinc(char const *s1, char s2)
{
	char	*str;
	int		i;

	i = 0;
	j = 0;
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

	i = 0;
	trigger = 0;
	while (*str)
	{		
		if (*str != c && trigger == 0)
		{
			if (*str == 34 || *str == 39)
			{
				d = *str;
				str++;
				while (*str != d)
					str++;
				str++;
			}
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

char	**ft_neosplit(char const *str, char c)
{
	int	i;
	int	j;
	char	d;	

	if (check_quote(str) == 0)
	{
		split = malloc(((count_words(s, c) + 1) * sizeof(char *)));
		if (!s || !split)
			return (0);
		i = 0;
		j = 0;
		index = -1;
		while (i <= ft_strlen(s))
		{
			if (s[i] != c && index < 0)
			{
				if (*str == 34 || *str == 39)
				{
					d = str[i++];
					while (str[i] != d)
						i++;
				}	
				index = i;
			}
			else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
			{
				split[j++] = word_dup(s, index, i);
				index = -1;
			}
			i++;
		}
		split[j] = 0;
		return (split);
	}
	else
		return (NULL);
}
