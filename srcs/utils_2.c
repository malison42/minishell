/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:35:48 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 11:43:06 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*remove_spaces(char *s)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	temp = s;
	s = ft_strtrim(s, " ");
	free(temp);
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	free(s);
	return (res);
}

void	get_dbl_quotes(t_cmd *new, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->i] == '"')
	{
		temp = double_quotes(s, env_lst, prs);
		tmp = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(tmp);
		free(temp);
		if (new->args[prs->arg_num] == NULL)
			new->args[prs->arg_num] = ft_strdup("");
	}
	if (s[prs->i] == '\'')
	{
		temp = single_quotes(s, prs);
		tmp = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(tmp);
		free(temp);
	}
}

char	*double_quotes(char *s, t_list *env, t_prs *prs)
{
	int		j;
	char	*file;
	char	*temp;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != '"')
		prs->i++;
	temp = ft_substr(s, j, prs->i - j);
	file = env_var_checker(temp, env, prs);
	free(temp);
	prs->i++;
	return (file);
}

char	*single_quotes(char *s, t_prs *prs)
{
	int		j;
	char	*file;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != '\'')
		prs->i++;
	file = ft_substr(s, j, prs->i - j);
	prs->i++;
	return (file);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
	{
		perror("dup2");
		exit(0);
	}
}
