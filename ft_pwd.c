/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-los- <tde-los-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:38:43 by tde-los-          #+#    #+#             */
/*   Updated: 2023/05/24 15:54:17 by tde-los-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_getpwd(t_data *data)
{
    char    *buff;

    buff = ft_calloc(4096 + 1, sizeof(char));
    getcwd(buff, 4096);
    data->pwd = buff;
    //printf("%s\n", buff);
    free(buff);
}