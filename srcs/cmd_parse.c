/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:27:43 by jshantay          #+#    #+#             */
/*   Updated: 2021/10/29 14:03:14 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*cmd_parse(t_list *cmd, char *line, t_list *env)
{
	char	**cmds;
//	t_cmd	*tmp;
//	t_list	*new;
	int		i;
	(void)env;

	i = 0;
	cmds = ft_split(line, 124);
	return (cmd);
}