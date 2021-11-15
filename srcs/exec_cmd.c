/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:39:58 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 15:55:32 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_envp(t_list *envp, char *key)
{
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		if (strcmp(key, env->key) == 0)
			return (env->value);
		envp = envp->next;
	}
	return (NULL);
}

char	**get_paths(t_list *envp)
{
	char	**paths;
	char	*path;

	path = get_envp(envp, "PATH");
	if (path != NULL)
	{
		paths = ft_split(path, ':');
		return (paths);
	}
	return (NULL);
}

void	ft_execve(char *path, char **args, char **tab)
{
	execve(path, args, tab);
	if (errno != 14)
		perror("minishell");
	exit(127);
}

void	exec_cmd(t_list *cmds, int *fd, t_list *env, int i)
{
	int		nbr_pipes;
	char	*cmd_path;
	char	**tab;
	t_cmd	*cmd;

	cmd_path = NULL;
	tab = list_to_arr(env);
	nbr_pipes = ft_lstsize(cmds) + i / 2 - 1;
	if (cmds->next)
		ft_dup2(fd[i + 1], 1);
	if (i != 0)
		ft_dup2(fd[i - 2], 0);
	close_fd(fd, nbr_pipes);
	cmd = cmds->content;
	/*
	 * нужно сделать так, чтобы при встрече редиректов или builtin
	 * они выполнялись и возвращали 1 при успешном выполнении в следующие if'ы
	 * Также надо сделать, чтобы каждый builtin возвращал статус завершения в
	 * нашу глобальную переменную
	 */
//	if (ft_redirect(cmd->redir))
//		exit(1);
//	if (exec_builtin(cmd, env, is_builtin(cmd)))
//		exit(g_exit_status);
	cmd_path = get_cmd_path(cmd->cmd, get_paths(env));
	ft_execve(cmd_path, cmd->args, tab);
}
