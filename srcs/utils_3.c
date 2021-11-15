/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:39:14 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 17:32:37 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmd(t_cmd *new, char *s, t_list *env)
{
	int		i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	allocate_args(s, new, env);
}

void	init_prs_cmd(t_prs *prs)
{
	prs->i = 0;
	prs->arg_num = 0;
	prs->ambiguous = 0;
	prs->ret_value = g_exit_status;
	prs->outside_quote = 0;
	prs->extra_args = NULL;
}

int	find_end_of_var(char *s, int i)
{
	if (ft_isdigit(s[i]))
		i++;
	else
		while (ft_isalnum(s[i]) || s[i] == '_')
			i++;
	return (i);
}

int	is_ambiguous_var_valid(char *var, char *joined)
{
	if (ft_strchr(var, '"') || ft_strchr(var, '\''))
	{
		free(var);
		free(joined);
		return (0);
	}
	return (1);
}

char	*get_ambiguous_var(char *joined, char *var)
{
	char	*temp;

	temp = NULL;
	temp = joined;
	joined = ft_strjoin(joined, "$");
	free(temp);
	temp = joined;
	joined = ft_strjoin(joined, var);
	free(temp);
	return (joined);
}
