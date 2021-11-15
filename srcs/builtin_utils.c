/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:18:56 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 17:16:14 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		return (2);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		return (3);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		return (4);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		return (5);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (6);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		return (7);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_list *env, int status)
{
	(void)cmd;
	(void)env;
	(void)status;
	return (1);
}
