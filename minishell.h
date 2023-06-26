/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:32:06 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/26 10:33:58 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*      Include     */
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
/*      Libft       */
# include "libft/libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/gnl/get_next_line.h"
/*      NAME        */
# define NAME "\033[1;36m☁️  Minichibre "
/*	STRUCTS	    */
typedef struct s_data
{
	char *pwd;
	char **env_cpy;
	int	env_len;
	char *home;
	char	**cmd;
	char	**cmd_full;
	int	pipenum;
	int	**pipes;
	int	fd1;
	int	fd2;
	int	*builtin;
	int	old_pipe[2];
	int	new_pipe[2];
}	t_data;

char	*ft_readline(void);
void	ft_getpwd(t_data *data);
void	ft_getenv(t_data *data, char **env);
void	ft_cd(t_data *data, char *prompt);
void	ft_gethome(t_data *data);
void	ft_parsing(t_data *data, char *prompt, char **env);
int	ft_echo(t_data *data, char *prompt);
void	ft_exit(t_data *data, char *prompt);
void	ft_freesplit(char **split);
void	ft_export(t_data *data, char *prompt);
void	ft_unset(t_data *data, char *prompt);
int	ft_lenvar(char *varName);
void	ft_ctrl_c(int signal);
void    ft_parsingg(t_data *data, char *prompt);
void	delete_tmpfile(char *file, t_data *data);
char	*ft_chk_cmd(t_data *data, int i);
char	*ft_strjoinc(char const *s1, char s2);

#endif
