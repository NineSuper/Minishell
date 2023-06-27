/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:18:59 by jcasades          #+#    #+#             */
/*   Updated: 2023/06/27 14:51:14 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_opentrunk(t_data *data, int i , int j)
{
    int fd;
    char *temp;
    char *arg;
    char *cmd;

    
    temp = ft_strjoin(cmd, " ");
    arg = ft_strjoin(temp, data->cmd_full[i + 1]);
    fd = open(arg, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    dup2(fd, 1);
    close(fd);
    free(cmd);
    free(temp);
    free(arg);
}
