/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:16:24 by jcasades          #+#    #+#             */
/*   Updated: 2023/06/19 11:15:26 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, int i)
{
	char	*cmd;
	pid_t	pid;
	int	status;

		cmd = ft_chk_cmd(data, i);
		if (cmd)
		{
				if (execve(cmd, ft_split(data->cmd_full[i], ' '), data->env_cpy) == -1)
					exit(1);
					//ft_printf("%d, %s\n", errno, strerror(errno));
			//waitpid(0, &status, 0);
		}
		else
			exit(1) ;
}

void	ft_exec(t_data *data, int i, int flag)
{
	int	j;

	j = 0;
	if (!data->cmd[0])
		exit(1) ;
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
	{
		ft_execve(data, i);
		//exit(1);
	}
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
	data->cmd_full=ft_split(prompt, '|');
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
		ft_freesplit(tmp);
		i++;
	}
	
	data->builtin = malloc((i + 1) * 4);
	i = 0;
	while (data->cmd[i])
	{
		is_builtin(data, data->cmd[i], i);
		i++;
	}
	//free(data->builtin);
	return (i);
}


void	ft_second_parse(t_data *data)
{
	pipe(data->old_pipe);
	pipe(data->new_pipe);

	// pipe(pipe);
	// data->pipes = malloc(sizeof (int *) * 3);
	// //data->pipes[0] = malloc(sizeof (int) * 2);
	// pipe(data->pipes[0]);
	// //data->pipes[1] = malloc(sizeof (int) * 2);
	// pipe(data->pipes[1]);
	// //data->pipes[2] = malloc(sizeof (int) * 2);
	// pipe(data->pipes[2]);
}

char	*ft_chk_cmd(t_data *data, int i)
{
	char	**pbl;
	char	**spt;
	int	j;
	char	*new_cmd;

	j = 0;
	while (ft_strncmp("PATH", data->env_cpy[j], 4))
		j++;
	pbl = ft_split(data->env_cpy[j], '=');
	spt = ft_split(pbl[1], ':');
	j = 0;
	while (spt[j])
	{
		new_cmd = ft_strjoin(spt[j], "/");
		if (access(ft_strjoin(new_cmd, data->cmd[i]), 0) == 0)
		{
			ft_freesplit(pbl);
			ft_freesplit(spt);
			return (ft_strjoin(new_cmd, data->cmd[i]));
		}
		free(new_cmd);
		j++;
	}
	ft_freesplit(pbl);
	ft_freesplit(spt);
	return (NULL);
}

void	ft_piping(t_data *data, int i)
{
	pid_t	pid;
	char *line;

	line = ft_calloc(1000000, 1);
	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
		{
			close(data->new_pipe[0]);
			dup2(data->fd1, 1);
			dup2(data->fd2, 0); 
			ft_exec(data, i, 1);
			close(data->new_pipe[1]);
		}
		else if (i == data->pipenum - 1) 
		{
			close(data->old_pipe[1]);
			dup2(data->old_pipe[0], 0);
			ft_exec(data, i, 1);
			close(data->old_pipe[0]);
		}
		else
		{
			close(data->old_pipe[1]);
			close(data->new_pipe[0]);
			dup2(data->old_pipe[0], 0);
			dup2(data->new_pipe[1], 1);
			ft_exec(data, i, 1);
			close(data->old_pipe[0]);
			close(data->new_pipe[1]);
		}
		read(data->new_pipe[0], line, 1000000);
		//ft_printf("%s\n", line);
		write(data->fd1, line, ft_strlen(line));
		read(data->old_pipe[0], line, 1000000);
		//ft_printf("%s\n", line);
		write(data->fd1, line, ft_strlen(line));
		data->old_pipe[0] = data->new_pipe[0];
		data->old_pipe[1] = data->new_pipe[1];
		
		
	}
	
	//waitpid(pid, NULL, 0);
	// ft_exec(data, i);
	// close(data->pipes[i % 2][1]);
	// close(data->pipes[(i + 1) % 2][0]);
	// close(data->pipes[0][1]);
	// close(data->pipes[i % 2][0]);		
		
}


void	single_cmd(t_data *data)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		ft_exec(data, 0, 1);
	waitpid(-1, NULL, 0);
}

/*void	delete_tmpfile(char *file, t_data *data)
{
	char	**argv;
	pid_t	pid;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "/bin/rm";
	ft_getpwd(data);
	argv[1] = ft_strjoin(ft_strjoin(data->pwd, "/"), file);
	argv[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/rm", argv, NULL);
}*/

void	ft_parsingg(t_data *data, char *prompt)
{
	int	i;
	int	fd;
	char	*line;
	i = 0;
	line = ft_calloc(1000000, 1);
	data->fd1 = open(".tmp1", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (!ft_first_parse(data, prompt))
		return ;
	ft_second_parse(data);
	if (data->pipenum == 1 && !ft_strncmp(data->cmd[0], "exit", 5))
		ft_exit(data, NULL);
	else if (data->pipenum == 1 && data->builtin[i])
		ft_exec(data, i, 0);
	else if (data->pipenum == 1)
		single_cmd(data);
	else
	{
		//ft_pipe(data, data->pipenum);
		while (data->cmd_full[i])
		{
			ft_piping(data, i);
			
			i++;
		}
		
		ft_printf("mdr\n");
		
	}
	
	ft_freesplit(data->cmd_full);
	ft_freesplit(data->cmd);
}


