/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:32:44 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 17:32:37 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	var_edge_cases(char *s, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->tmp.i] == '$' && s[prs->tmp.i + 1] == '?')
	{
		tmp = prs->tmp.res;
		prs->tmp.i += 2;
		prs->tmp.res = ft_strjoin(prs->tmp.res,
			temp = ft_itoa(prs->ret_value));
		free(temp);
		free(tmp);
	}
	if (s[prs->tmp.i] == '$' && s[prs->tmp.i + 1] == '$')
	{
		tmp = prs->tmp.res;
		prs->tmp.i += 2;
		prs->tmp.res = ft_strjoin(prs->tmp.res, temp = ft_itoa(99844));
		free(temp);
		free(tmp);
	}
}

static void	get_variable(char *s, t_list *env, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*tmp;

	prs->tmp.i++;
	j = prs->tmp.i;
	if (ft_isdigit(s[prs->tmp.i]))
		prs->tmp.i++;
	else
		while (ft_isalnum(s[prs->tmp.i]) || s[prs->tmp.i] == '_')
			prs->tmp.i++;
	tmp = ft_substr(s, j, prs->tmp.i - j);
	temp = variable_expander(tmp, env);
	if (prs->outside_quote && ft_strchr(temp, ' '))
	{
		temp = remove_spaces(temp);
		prs->extra_args = ft_split(temp, ' ');
		free(temp);
		temp = prs->extra_args[0];
	}
	free(tmp);
	tmp = prs->tmp.res;
	prs->tmp.res = ft_strjoin(prs->tmp.res, temp);
	free(temp);
	free(tmp);
}

static void	check_var_edge_cases(char *s, t_list *env, t_prs *prs)
{
	char	*tmp;

	var_edge_cases(s, prs);
	if (s[prs->tmp.i] == '$' && (s[prs->tmp.i + 1] == ' '
								 || s[prs->tmp.i + 1] == '\0'))
	{
		tmp = prs->tmp.res;
		prs->tmp.i++;
		prs->tmp.res = ft_strjoin(prs->tmp.res, "$");
		free(tmp);
	}
	else if (s[prs->tmp.i] == '$')
		get_variable(s, env, prs);
}

char	*env_var_checker(char *s, t_list *env, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*tmp;

	prs->tmp.res = NULL;
	temp = NULL;
	prs->tmp.i = 0;
	while (s[prs->tmp.i])
	{
		j = prs->tmp.i;
		while (s[prs->tmp.i] && s[prs->tmp.i] != '$')
			prs->tmp.i++;
		tmp = prs->tmp.res;
		temp = ft_substr(s, j, prs->tmp.i - j);
		prs->tmp.res = ft_strjoin(prs->tmp.res, temp);
		free(temp);
		free(tmp);
		check_var_edge_cases(s, env, prs);
	}
	return (prs->tmp.res);
}

int	ambiguous_err_msg(char *expanded, char *joined, t_prs *prs, int i)
{
	if (!expanded || ft_strchr(expanded, ' '))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(joined, 2);
		err_msg(": ambiguous redirect");
		free(joined);
		prs->i = i;
		return (-1);
	}
	free(joined);
	free(expanded);
	return (0);
}