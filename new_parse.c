/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:16:24 by jcasades          #+#    #+#             */
/*   Updated: 2023/06/12 15:37:28 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	is_builtin(t_data *data, char *cmd, int i)
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
*/
void	ft_first_parse(t_data *data, char *prompt)
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
//	data->builtin = malloc((i + 1) * 4);
//	i = 0;
//	while (data->cmd[i])
//	{
//		is_builtin(data, data->cmd[i], i);
//		i++;
//	}
	//free(data->builtin);
}


void	ft_second_parse(t_data *data)
{
	data->pipes = malloc(sizeof (int *) * 2);
	data->pipes[0] = malloc(sizeof (int) * 2);
	pipe(data->pipes[0]);
	data->pipes[1] = malloc(sizeof (int) * 2);
	pipe(data->pipes[1]);
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
		
void	ft_execve(t_data *data, int i)
{
	char	*cmd;
	//pid_t	pid;

	//if (pid == 0)
	//{
		cmd = ft_chk_cmd(data, i);
		if (cmd)
		{	
			if (execve(cmd, ft_split(data->cmd_full[i], ' '), data->env_cpy) == -1)
				ft_printf("%d, %s\n", errno, strerror(errno));
		//	exit(1);
		}
		else
			exit(EXIT_SUCCESS) ;
	//}
}

void	ft_exec(t_data *data, int i)
{
	int	j;

	j = 0;
	if (!data->cmd[0])
		exit(1) ;
	if (!ft_strncmp(data->cmd[i], "cd", 3))
	{
		ft_cd(data, data->cmd_full[i], data->env_cpy);
		exit(1);
	}
	else if (!ft_strncmp(data->cmd[i], "echo", 5))
	{
		ft_echo(data, data->cmd_full[i]);
		exit(1);
	}
	else if (!ft_strncmp(data->cmd[i], "export", 7))
	{
		ft_export(data, data->cmd_full[i]);
		exit(1);
	}
	else if (!ft_strncmp(data->cmd[i], "unset", 6))
	{
		ft_unset(data, data->cmd_full[i]);
		exit(1);
	}
	else if (!ft_strncmp(data->cmd[i], "env", 4))
	{
		while (data->env_cpy[j])
			ft_printf("%s\n", data->env_cpy[j++]);
		exit(1);
	}
	else if (!ft_strncmp(data->cmd[i], "pwd", 4))
	{
		ft_getpwd(data);
		ft_printf("%s\n", data->pwd);
		exit(1);
	}		
	else if (!ft_strncmp(data->cmd[i], "exit", 5))
	{
		
		ft_exit(data, NULL);
		kill(0, SIGKILL);
	}
	else
		ft_execve(data, i);
}

void	ft_piping(t_data *data, int i)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
		{
			dup2(data->fd1, 0);
			dup2(data->pipes[0][1], 1);
			ft_exec(data, i);
			close(data->pipes[0][1]);
		}
		else if (i == data->pipenum - 1) 
		{
			dup2(data->pipes[(i + 1) % 2][0], 0);
			dup2(data->fd2, 1);
			ft_exec(data, i);
			close(data->pipes[(i + 1) % 2][0]);	
		}
		else
		{
			dup2(data->pipes[(i + 1) % 2][0], 0);
			dup2(data->pipes[i % 2][1], 1);
			ft_exec(data, i);
			close(data->pipes[i % 2][1]);
			close(data->pipes[(i + 1) % 2][0]);
		}	
		//ft_exec(data, i);	
	}	
}

void	single_cmd(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_exec(data, 0);
	wait(NULL);
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
	ft_first_parse(data, prompt);
	ft_second_parse(data);
	data->fd1 = open(".tmp1", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	data->fd2 = open(".tmp2", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (data->pipenum == 1 && !ft_strncmp(data->cmd[0], "exit", 5))
		ft_exit(data, NULL);
	if (data->pipenum == 1)
		single_cmd(data);
	else
	{
		while (data->cmd_full[i])
		{
			ft_piping(data, i);
			i++;
		}
		close(data->fd2);
		data->fd2 = open(".tmp2", O_RDONLY);
		line = get_next_line(data->fd2);
		while (line)
		{
			ft_printf("%s", line);
			line = get_next_line(data->fd2);
		}
		close(data->fd2);
		data->fd2 = open(".tmp2", O_TRUNC | O_WRONLY);
		close(data->pipes[0][0]);
		close(data->pipes[0][1]);
		close(data->pipes[1][0]);
		close(data->pipes[1][1]);
		close(data->fd1);
		close(data->fd2);
	}
	
	ft_freesplit(data->cmd_full);
	ft_freesplit(data->cmd);
}


