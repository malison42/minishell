/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:46:12 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 18:03:20 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	set_exit_status(int cnt_cmd)
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	}
	wait_cmds(cnt_cmd);
}

void	close_fd(int *fd, int nbr)
{
	int	i;

	i = 0;
	while (i < 2 * nbr)
	{
		close(fd[i]);
		i++;
	}
}

int	create_childs(t_list *cmds, int *fd, t_list *env)
{
	int	i;
	int	pid;

	i = 0;
	while (cmds)
	{
		pid = fork();
		if (pid == 0)
			exec_cmd(cmds, fd, env, i);
		cmds = cmds->next;
		i += 2;
	}
	return (pid);
}

int	*create_pipes(int nbr_pipes)
{
	int	*fd;
	int	i;

	fd = malloc(2 * nbr_pipes * sizeof(int));
	i = 0;
	while (i < nbr_pipes)
	{
		if (pipe(fd + 2 * i) < 0)
		{
			perror("pipe: ");
			exit(0);
		}
		i++;
	}
	return (fd);
}

void	exec(t_list *cmd, t_list *env)
{
	int	cnt_cmd;
	int	*fd;
	int	pid;

	fd = NULL;
	cnt_cmd = ft_lstsize(cmd);
	if (cnt_cmd > 0)
	{
		if (cnt_cmd > 1)
			fd = create_pipes(cnt_cmd - 1);
		pid = create_childs(cmd, fd, env);
		if (cnt_cmd > 1)
			close_fd(fd, cnt_cmd - 1);
		waitpid(pid, &g_exit_status, 0);
		set_exit_status(cnt_cmd);
	}
}