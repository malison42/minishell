/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:37:52 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 15:37:52 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_cmds(int cnt_cmd)
{
	int	i;

	i = 0;
	while (i < cnt_cmd)
	{
		wait(NULL);
		i++;
	}
}

static char	*ft_join(t_env *env)
{
	char	*tab;
	char	*tmp;

	if (env->value != NULL)
	{
		tmp = ft_strjoin(env->key, "=");
		tab = ft_strjoin(tmp, env->value);
		free(tmp);
		return (tab);
	}
	return (env->key);
}

char	**list_to_arr(t_list *lst)
{
	int		i;
	int		size;
	char	**tab;
	t_env	*env;

	size = ft_lstsize(lst) + 1;
	tab = malloc(size * sizeof(char *));
	i = 0;
	while (i < size - 1)
	{
		env = lst->content;
		tab[i] = ft_join(env);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static char	*ft_local_cmd(char *str, char *cmd)
{
	int	j;

	j = open(str, O_RDONLY);
	if (j != -1 && j != 13)
		return (str);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	int		j;
	char	*str;
	char	*str2;

	str2 = cmd;
	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	if (cmd[0] != '\0' && paths != NULL)
	{
		cmd = ft_strjoin("/", cmd);
		i = 0;
		while (paths[i] != NULL)
		{
			str = ft_strjoin(paths[i], cmd);
			j = open(str, O_RDONLY);
			if (j != -1 && j != 13)
				return (str);
			free(str);
			i++;
		}
	}
	return (ft_local_cmd(str2, cmd));
}
