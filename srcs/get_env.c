/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 14:48:44 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/08 11:22:27 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*new_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->flag = 1;
	return (new);
}

char	*get_key(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	temp = ft_substr(s, 0, i);
	return (temp);
}

char	*get_value(char *s)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (s[i] != '=' && s[i])
		i++;
	if (s[i] == '=')
		temp = ft_substr(s, i + 1, ft_strlen(s) - i);
	return (temp);
}

static char	*get_shell_lvl(char *value)
{
	char	*temp;

	temp = value;
	value = ft_itoa(ft_atoi(value) + 1);
	free(temp);
	return (value);
}

void	save_env(t_list **env, char **envp)
{
	t_list	*new;
	t_env	*tmp;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (!ft_strcmp(key, "SHLVL"))
			value = get_shell_lvl(value);
		tmp = new_node(key, value);
		new = ft_lstnew(tmp);
		ft_lstadd_back(env, new);
		free(key);
		free(value);
		i++;
	}
}
