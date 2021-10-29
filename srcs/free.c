/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:16:14 by jshantay          #+#    #+#             */
/*   Updated: 2021/10/29 14:29:40 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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