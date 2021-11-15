/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:16:14 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 16:55:23 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_redirect(t_list *redir)
{
	t_list	*redir_temp;
	t_redir	*temp;

	while (redir != NULL)
	{
		redir_temp = redir;
		temp = redir->content;
		if (temp->file)
			free(temp->file);
		free(temp);
		redir = redir->next;
		free(redir_temp);
	}
}

void	free_cmd_list(t_list *cmd)
{
	t_list		*list_temp;
	t_cmd		*temp;
	int			i;

	i = 0;
	while (cmd != NULL)
	{
		list_temp = cmd;
		temp = cmd->content;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
				free(temp->args[i++]);
			free(temp->args);
		}
		if (temp->redir)
			free_redirect(temp->redir);
		free(temp);
		cmd = cmd->next;
		free(list_temp);
	}
	cmd = NULL;
}

void	free_env(t_list *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env->content;
		free(temp->key);
		free(temp->value);
		free(env->content);
		free(env);
		env = env->next;
	}
}