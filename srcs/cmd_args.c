/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:08:42 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 17:32:37 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*variable_expander(char *key, t_list *env)
{
	t_env	*temp;
	char	*expanded;

	expanded = NULL;
	while (env != NULL)
	{
		temp = env->content;
		if (!(ft_strcmp(key, temp->key)))
			expanded = ft_strdup(temp->value);
		env = env->next;
	}
	return (expanded);
}

static int	args_counter(char *s)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] == ' ')
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

int	count_extra_args(char *s, int i, int j, t_list *env)
{
	char	*temp;
	char	*tmp;
	int		ret;

	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != '"'
				   && s[i] != '\'' && s[i] != '$')
				i++;
			temp = ft_substr(s, j, i - j);
			tmp = variable_expander(temp, env);
			free(temp);
			if (ft_strchr(tmp, ' '))
				ret += args_counter(tmp);
			free(tmp);
		}
	}
	return (ret);
}

void	allocate_args(char *s, t_cmd *cmd, t_list *env)
{
	/*
	 * выделяем память под комманды и аргументы, если в аргументах
	 * переменная окружения, то она вытягивается и память аллоцируется под ее
	 * содержимое в функции count_extra_args
	 */
	int		ret;
	int		i;

	ret = get_size(s);
	if (ft_strchr(s, '$'))
		ret += count_extra_args(s, 0, 0, env);
	cmd->args = malloc(sizeof(char *) * (ret + 1));
	i = 0;
	while (i <= ret)
		cmd->args[i++] = NULL;
}
