/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:32:06 by ltressen          #+#    #+#             */
/*   Updated: 2023/06/28 12:58:23 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DQUOTE 1
# define SQUOTE 2
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
typedef struct s_arg
{
	char	**argq;
	int	*flaq;
}	t_arg;
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
	int	term;
	int	termo;
	int	*builtin;
	char	*oldstatus;
	int	old_pipe[2];
	int	new_pipe[2];
	int	errnum;
	t_arg	args;
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
char	*ft_reparg(t_data *data, int i, int j);
char	*ft_strjoinc(char *s1, char s2);
char	**ft_neosplit(char *str, char c);
int	ft_opentrunk(t_data *data, int i, int j);
int	ft_openapp(t_data *data, int i, int j);
int	ft_input(t_data *data, int i, int j);
int	ft_limit(t_data *data, int i, int j);

#endif