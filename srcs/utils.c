/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:15 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/08 00:43:10 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_size(char *s)
{
	int		i;
	int		quote;
	int		ret;

	ret = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		i = skip_space_and_redir(s, i);
		if (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		{
			while ((s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				   || (s[i] == ' ' && quote)
				   || ((s[i] == '>' || s[i] == '<') && quote))
				quote = check_for_quote(s[i++], quote);
			ret++;
		}
	}
	return (ret);
}

void	fill_arg(char *temp, t_cmd *new, t_list *env, t_prs *prs)
{
	char	*tmp;

	tmp = env_var_checker(temp, env, prs);
	free(temp);
	temp = new->args[prs->arg_num];
	new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], tmp);
	free(temp);
	free(tmp);
}

void	add_extra_args(t_cmd *new, t_prs *prs)
{
	int		i;

	i = 1;
	while (prs->extra_args[i])
	{
		new->args[prs->arg_num + i] = prs->extra_args[i];
		i++;
	}
	i = 1;
	while (prs->extra_args[i])
	{
		prs->arg_num++;
		i++;
	}
	free(prs->extra_args);
	prs->extra_args = NULL;
}

static void	is_arg_empty(t_cmd *new, char *s, t_prs *prs, int j)
{
	char	*temp;

	temp = ft_substr(s, j, prs->i - j);
	prs->arg_num++;
	if (!ft_strcmp(new->args[prs->arg_num - 1], "")
		&& (temp[0] == '$' && !ft_strchr(temp, '"')
		&& !ft_strchr(temp, '\'')))
	{
		prs->arg_num--;
		free(new->args[prs->arg_num]);
		new->args[prs->arg_num] = NULL;
	}
	free(temp);
}

void	get_arg(t_cmd *new, char *s, t_list *env, t_prs *prs)
{
	char	*temp;
	int		j;

	temp = NULL;
	j = prs->i;
	if (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != '\'' && s[prs->i]
		&& s[prs->i] != '<' && s[prs->i] != '>')
	{
		while (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != '\''
			   && s[prs->i] && s[prs->i] != '<' && s[prs->i] != '>')
			prs->i++;
		prs->outside_quote = 1;
		temp = ft_substr(s, j, prs->i - j);
		fill_arg(temp, new, env, prs);
		if (prs->extra_args)
			add_extra_args(new, prs);
		prs->outside_quote = 0;
	}
	if (s[prs->i] == '"' || s[prs->i] == '\'')
		get_dbl_sgl_quotes(new, s, env, prs);
	if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>' || s[prs->i] == '<')
		is_arg_empty(new, s, prs, j);
}
