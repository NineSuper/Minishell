/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:35:09 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/03 12:59:53 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, int i)
{
	char	*cmd;

	cmd = ft_chk_cmd(data, i);
	if (cmd)
	{
		if (execve(cmd, ft_split(data->cmd_full[i], ' '), data->env_cpy) == -1)
		{
<<<<<<< HEAD
			if (execve(cmd, ft_split(data->cmd_full[i], ' '), data->env_cpy) == -1)
			{
				ft_printf("%d %s\n", errno, strerror(errno));
				perror("Error is :");
				free(cmd);
				exit(1);
			}
=======
			data->errnum = errno;
			perror("Error");
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
			free(cmd);
			exit(0);
		}
<<<<<<< HEAD
		else
			exit(1) ;
=======
		free(cmd);
		exit(0);
	}
	else
		exit(0);
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
}

int	ft_third_parse(t_data *data, int i)
{
	char	*new_cmd;
	char	*arg;
<<<<<<< HEAD
	int	j;
	int	k;
	int	fd;
=======
	char	*error;
	int		j;
	int		k;
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99

	j = 0;
	k = 0;
	error = ft_itoa(data->errnum >> 8);
	new_cmd = ft_calloc(1, 1);
	while (data->cmd_full[i][j])
	{
		while (data->cmd_full[i][j] != '<' && data->cmd_full[i][j] != '>'
			&& data->cmd_full[i][j] != '\'' && data->cmd_full[i][j] != '"'
			&& data->cmd_full[i][j] != '$' && data->cmd_full[i][j] != ' '
			&& data->cmd_full[i][j])
		{
			new_cmd = ft_strjoinc(new_cmd, data->cmd_full[i][j]);
			j++;
			k++;
		}
		if (data->cmd_full[i][j] == ' ')
		{
			new_cmd = ft_strjoinc(new_cmd, ' ');
			k++;
			j++;
			while (data->cmd_full[i][j] == ' ')
				j++;
		}
		if (data->cmd_full[i][j] == '<')
		{
			if (data->cmd_full[i][j + 1] == '<')
			{
<<<<<<< HEAD
				j = ft_limit(data, i , j); //fonction pour prendre un delimiteur et qui attends un input
=======
				j = ft_limit(data, i, j);
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
				j++;
			}
			else
			{
<<<<<<< HEAD
				j = ft_input(data, i , j); //fonction pour redirect l'entree
				if (j == 0)
					return(0);
=======
				j = ft_input(data, i, j);
				if (j == 0)
					return (0);
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
				j++;
			}
		}
		if (data->cmd_full[i][j] == '>')
		{
			if (data->cmd_full[i][j + 1] == '>')
			{
<<<<<<< HEAD
				j = ft_openapp(data, i , j); //fonction pour dup/open en APPEND et ecrire dans un fichier
=======
				j = ft_openapp(data, i, j);
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
				j++;
			}
			else
			{
<<<<<<< HEAD
				j = ft_opentrunk(data, i , j);
				j++; 
=======
				j = ft_opentrunk(data, i, j);
				j++;
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
			}
		}
		if (data->cmd_full[i][j] == '\'')
		{
			j++;
			while (data->cmd_full[i][j] != '\'' && data->cmd_full[i][j] != '\0')
			{
				new_cmd = ft_strjoinc(new_cmd, data->cmd_full[i][j]);
				j++;
			}
			if (data->cmd_full[i][j] == '\0')
			{
				ft_printf("error");
				exit(1);
			}
			else
				j++;
		}
		if (data->cmd_full[i][j] == '"')
		{
			j++;
			while (data->cmd_full[i][j] != '"' && data->cmd_full[i][j] != '\0')
			{
				if (data->cmd_full[i][j] == '$')
				{	
					if (data->cmd_full[i][j + 1] != '?')
					{
						arg = ft_reparg(data, i, j);
						new_cmd = ft_strjoinfree(new_cmd, arg);
						if (arg)
							free(arg);
					}
					else
						new_cmd = ft_strjoinfree(new_cmd, error);
					while (data->cmd_full[i][j] != ' '
					&& data->cmd_full[i][j] != '"')
						j++;
				}
				j++;
			}
		}
		if (data->cmd_full[i][j] == '$')
		{
			if (data->cmd_full[i][j + 1] != '?')
			{
				arg = ft_reparg(data, i, j);
				new_cmd = ft_strjoinfree(new_cmd, arg);
				if (arg)
					free(arg);
			}
			else
				new_cmd = ft_strjoinfree(new_cmd, error);
			while (data->cmd_full[i][j] != ' ' && data->cmd_full[i][j] != '\0')
				j++;
		}
	}
	free(error);
	free(data->cmd_full[i]);
	data->cmd_full[i] = ft_strdup(new_cmd);
	free(new_cmd);
	return (1);
}
<<<<<<< HEAD



void	ft_exec(t_data *data, int i, int flag)
{
	int	j;

	j = 0;
	if (!ft_third_parse(data, i))
		exit(1);
	if (!data->cmd[0])
		exit(1);
	if (!ft_strncmp(data->cmd[i], "cd", 3))
		ft_cd(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "echo", 5))
		ft_echo(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "export", 7))
		ft_export(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "unset", 6))
		ft_unset(data, data->cmd_full[i]);
	else if (!ft_strncmp(data->cmd[i], "env", 4))
		while (data->env_cpy[j])
			ft_printf("%s\n", data->env_cpy[j++]);
	else if (!ft_strncmp(data->cmd[i], "pwd", 4))
	{
		ft_getpwd(data);
		ft_printf("%s\n", data->pwd);
	}		
	else if (!ft_strncmp(data->cmd[i], "exit", 5))
		ft_exit(data, NULL);
	else
		ft_execve(data, i);
	if ((!ft_strncmp(data->cmd[i], "cd", 3) || !ft_strncmp(data->cmd[i], "echo", 5) || !ft_strncmp(data->cmd[i], "export", 7) || !ft_strncmp(data->cmd[i], "unset", 6) || !ft_strncmp(data->cmd[i], "env", 4) || !ft_strncmp(data->cmd[i], "pwd", 4)) && flag == 1)
		exit(1);

}

void	is_builtin(t_data *data, char *cmd, int i)
{

	if (!ft_strncmp(cmd, "cd", 3))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "echo", 5))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "export", 7))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "unset", 6))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "env", 4))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "pwd", 4))
		data->builtin[i] = 1;
	else if (!ft_strncmp(cmd, "exit", 5))
		data->builtin[i] = 1;
	else
		data->builtin[i] = 0;
}

int	ft_first_parse(t_data *data, char *prompt)
{
	int	i;
	int	j;
	char	**tmp;

	i = 0;
	data->cmd_full=ft_neosplit(prompt, '|');
	if (!data->cmd_full)
		return (0);
	while (data->cmd_full[i])
		i++;
	data->pipenum = i;	
	data->cmd = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (data->cmd_full[i])
	{
		tmp = ft_split(data->cmd_full[i], ' ');
		if (tmp[0])
			data->cmd[i] = ft_strdup(tmp[0]);
		else
		{
			ft_freesplit(data->cmd_full);
			ft_freesplit(data->cmd);
			ft_freesplit(tmp);
			return (i);
		}
		ft_freesplit(tmp);
		i++;
	}
	return (i);
}


void	ft_second_parse(t_data *data)
{
	int	i;
	i = 0;

	data->pipes = ft_calloc(data->pipenum, sizeof(int *));
	while (i < data->pipenum - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		pipe(data->pipes[i]);
		i++;
	}
}

char	*ft_chk_cmd(t_data *data, int i)
{
	char	**pbl;
	char	**spt;
	int	j;
	char	*new_cmd;
	char	*temp;

	j = 0;
	if (data->cmd_full[i][j] == '.')
		return(data->cmd[i]);
	while (ft_strncmp("PATH", data->env_cpy[j], 4))
		j++;
	pbl = ft_split(data->env_cpy[j], '=');
	spt = ft_split(pbl[1], ':');
	j = 0;
	while (spt[j])
	{
		new_cmd = ft_strjoin(spt[j], "/");
		temp = ft_strjoin(new_cmd, data->cmd[i]);
		if (access(temp, 0) == 0)
		{
			ft_freesplit(pbl);
			ft_freesplit(spt);
			free(new_cmd);
			return (temp);
		}
		free(temp);
		free(new_cmd);
		j++;
	}
	ft_freesplit(pbl);
	ft_freesplit(spt);
	dup2(data->term, 1);
	return (NULL);
}
void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipes[i])
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}
pid_t	ft_piping(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
		{
			dup2(data->pipes[i][1], 1);	
		}
		else if (i == data->pipenum - 1) 
		{
			dup2(data->pipes[i - 1][0], 0);
		}
		else
		{
			dup2(data->pipes[i- 1][0], 0);
			dup2(data->pipes[i][1], 1);
		}
		close_pipes(data);
		ft_exec(data, i, 1);
	}
	return (pid);
}


void	single_cmd(t_data *data)
{
	pid_t pid;
	int	exit_status;

	pid = fork();
	if (pid == 0)
		ft_exec(data, 0, 1);
	waitpid(-1, &data->errnum, 0);
}

void	ft_parsingg(t_data *data, char *prompt)
{
	int	i;
	int pid;
	
	i = 0;
	if (!ft_first_parse(data, prompt))
		return ;
	if (data->pipenum > 1)
		ft_second_parse(data);
	if (data->pipenum == 1 && !ft_strncmp(data->cmd[0], "exit", 5))
		ft_exit(data, prompt);
	else if (data->pipenum == 1 && ((!ft_strncmp(data->cmd[i], "cd", 3) || !ft_strncmp(data->cmd[i], "echo", 5) || !ft_strncmp(data->cmd[i], "export", 7) || !ft_strncmp(data->cmd[i], "unset", 6) || !ft_strncmp(data->cmd[i], "env", 4) || !ft_strncmp(data->cmd[i], "pwd", 4))))
		ft_exec(data, i, 0);
	else if (data->pipenum == 1)
		single_cmd(data);
	else
	{
		while (data->cmd_full[i])
		{
			pid = ft_piping(data, i);
			i++;
		}
		close_pipes(data);
		i = 0;
		while (i < data->pipenum)
		{
			waitpid(-1, &data->errnum, 0);
			i++;
		}
		ft_freesplit((char **)data->pipes);
	}
	dup2(data->term, 1);
	dup2(data->termo, 0);
	ft_freesplit(data->cmd_full);
	ft_freesplit(data->cmd);
}


=======
>>>>>>> 5c98730e42ab3e9996f2c305fdab1d147595fa99
