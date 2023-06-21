/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:38:43 by tde-los-          #+#    #+#             */
/*   Updated: 2023/06/21 14:11:43 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_getpwd(t_data *data)
{
    char    *buff;
    if (data->pwd)
	    free(data->pwd);
    buff = ft_calloc(4096 + 1, sizeof(char));
    getcwd(buff, 4096);
    data->pwd = ft_strdup(buff);
    free(buff);
}
