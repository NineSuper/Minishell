/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:40:33 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/26 13:21:54 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
todo faire une fonction qui renvoie la chaine de caractere suivante :
? echo "USER" = USER
* echo "$USER" = tde-los-
! echo "$USEEEEEEER" = ' '

? echo 'PWD' | '$PWD' = PWD

* echo "'$USER'" "'MDR'" = 'tde-los' 'MDR'

? echo '"$OLDPWD"' '"TEST"' = "OLDPWD" "TEST"

* Si ' ' = toujours renvoyer le contenu brut
*/

int	ft_check_quote(char *str)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = 0;
	c = str[0];
	if (str[0] == 39 || str[0] == '"')
		j++;
	while (str[++i])
		if (i > 1 && str[i] == c)
			j++;
	if (j % 2 != 0)
		return (0);
	return (j);
}

char	*ft_simple_quote(t_data *data, char *str)
{
	char	*src;
	int		i;

	i = 0;
	while (str[i] == 39)
		i++;
	src = malloc(sizeof(char) * (ft_strlen(str) - (i + i)) + 1);
	while (str[i])
	{
		src[i] = str[i];
		i++;
	}
	src[i] = '\0';
	printf("SRC : %s\n", src);
	return (src);
}

char	*ft_double_quote(t_data *data, char *str)
{
	char	*src;
}

char	*ft_quote(t_data *data, char *str)
{
	char	*new_str;

	if (!ft_check_quote(str))
		return ("Error\n");
	if (str[0] == 39)
		new_str = ft_simple_quote(data, str);
	if (str[0] == '"')
		new_str = "bite";
		//new_str = ft_double_quote(data, str);
	return (new_str);
}
