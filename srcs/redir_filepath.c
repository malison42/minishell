/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_filepath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:28:25 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 17:32:37 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_ambiguous_redir(char *s, t_list *env, t_prs *prs)
{
	char	*var;
	char	*expanded;
	char	*joined;
	int		i;
	int		j;

	expanded = NULL;
	joined = NULL;
	i = prs->i;
	while (!expanded && s[i] == '$')
	{
		i++;
		j = i;
		i = find_end_of_var(s, i);
		var = ft_substr(s, j, i - j);
		if (!is_ambiguous_var_valid(var, joined))
			return (0);
		joined = get_ambiguous_var(joined, var);
		expanded = variable_expander(var, env);
		free(var);
	}
	if (!ambiguous_err_msg(expanded, joined, prs, i))
		return (0);
	return (-1);
}

void	join_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*tmp;
	int		j;

	j = prs->i;
	if (s[prs->i] && s[prs->i] != '"' && s[prs->i] != '\''
		&& s[prs->i] != '>' && s[prs->i] != '<')
	{
		while (s[prs->i] && s[prs->i] != ' ' && s[prs->i] != '<'
			   && s[prs->i] != '>' && s[prs->i] != '"' && s[prs->i] != '\'')
			prs->i++;
		temp = ft_substr(s, j, prs->i - j);
		tmp = env_var_checker(temp, env_lst, prs);
		free(temp);
		temp = redir->file;
		redir->file = ft_strjoin(redir->file, tmp);
		free(tmp);
		free(temp);
	}
}

void	get_file_quote(t_redir *redir, char *s, t_list *env, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->i] == '"')
	{
		temp = double_quotes(s, env, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
		if (redir->file == NULL)
			redir->file = ft_strdup("");
	}
	if (s[prs->i] == '\'')
	{
		temp = single_quotes(s, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
	}
}

void	get_filepath(t_redir *redir, char *s, t_list *env, t_prs *prs)
{
	while (s[prs->i] == ' ')
		prs->i++;
	if (s[prs->i] == '$')
		/*
		 * в функции ниже проверяется неопределенный редирект,
		 * например echo "cat" >> $NONEXIT
		 */
		if (check_ambiguous_redir(s, env, prs) == -1)
			prs->ambiguous = 1;
	while (s[prs->i])
	{
		join_filepath(redir, s, env, prs);
		get_file_quote(redir, s, env, prs);
		if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>'
			|| s[prs->i] == '<')
			break ;
	}
	while (s[prs->i] == ' ')
		prs->i++;
}

static char	get_redir_type(char first, char second)
{
	if (first == '>' && second != '>')
		return ('O');
	else if (first == '<' && second != '<')
		return ('I');
	else if (first == '>' && second == '>')
		return ('A');
	else if (first == '<' && second == '<')
		return ('H');
	return (0);
}

t_redir	*new_redir(char *s, t_list *env, t_prs *prs)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = NULL;
	new->type = '\0';
	while (s[prs->i] == ' ')
		prs->i++;
	new->type = get_redir_type(s[prs->i], s[prs->i + 1]);
	if (new->type == 'O' || new->type == 'I')
	{
		prs->i++;
		get_filepath(new, s, env, prs);
	}
	else
	{
		prs->i += 2;
		get_filepath(new, s, env, prs);
	}
	return (new);
}

t_list	*redir(t_list *redir, char *s, t_list *env, t_prs *prs)
{
	t_list		*new;
	t_redir		*tmp;

	while (s[prs->i])
	{
		if (s[prs->i] && s[prs->i] != '>' && s[prs->i] != '<')
			break ;
		tmp = new_redir(s, env, prs);
		new = ft_lstnew(tmp);
		ft_lstadd_back(&redir, new);
	}
	return (redir);
}
