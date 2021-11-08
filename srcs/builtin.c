/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malison <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 21:43:39 by malison           #+#    #+#             */
/*   Updated: 2021/11/08 16:33:03 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
void	copy_envp(char **exp, char **env)
{
	int i;

	i = 0;
	while (env[i])
		size++;
	exp = malloc((i + 1) * sizeof(*env));
	i = 0;
	while (env[i])
	{
		exp[i] = ft_strdup(env[i]);
		i++;
	}
	exp[i] = NULL;
}
 */

int	ft_echo(char **str, int fd)
{
	int	i;
	int n;
	int rez;

	rez = 0;
	if (!str)
		return (-1);
	i = 0;
	n = 0;
	if (!ft_strcmp(str[i], "-n"))
	{
		n = 1;
		i++;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[++i])
			write(fd, " ", 1);
	}
	if (n == 0)
		write(fd,"\n", 1);
	return (rez);
}

int	ft_cd(char *str)
{
	int rez;

	rez = chdir(str);
	return (rez);
}

void	ft_pwd(int fd)
{
	char *buf;
	char *pwd;

	buf = NULL;
	pwd = getcwd(buf, 0);
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
//	printf("%s\n", getcwd(buf, 0));
	free(buf);
	free(pwd);
}

void 	ft_env(t_list **env, int fd)
{
	t_list	*lst;
	t_env	*var;

	lst = *env;
	while (lst)
	{
		var = lst->content;
		if (var->flag == 1)
		{
			ft_putstr_fd(var->key, fd);
			write(fd, "=", 1);
			if (var->value)
				ft_putstr_fd(var->value, fd);
			write(fd, "\n", 1);
		}
		lst = lst->next;
	}
}

t_list	*check_list_env(t_list **env, char *key)
{
	t_list	*lst;
	t_env	*tmp;

	lst = *env;
	while (lst)
	{
		tmp = lst->content;
		if (!ft_strcmp(tmp->key, key))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	print_export(t_list **env, int fd)
{
	t_list	*lst;
	t_env	*var;

	lst = *env;
	while (lst)
	{
		var = lst->content;
		if (var->flag)
		{
			ft_putstr_fd(var->key, fd);
			write(fd, "=", 1);
			if (var->value)
				ft_putstr_fd(var->value, fd);
			else
				write(fd, "\'\'", 2);
			write(fd, "\n", 1);
		}
		lst = lst->next;
	}
}

void	ft_export(t_list **env, char **args, int fd)
{
	int		i;
	char 	*key;
	char 	*value;
	t_list	*lst;
	t_env	*var;

	if (!args)
		print_export(env, fd);
	i = 0;
	while (args[i])
	{
		key = get_key(args[i]);
		lst = check_list_env(env, key);
		if (lst)
		{
			var = lst->content;
			var->flag = 1;
			if (ft_strchr(args[i], 61))
			{
				free(var->value);
				var->value = get_value(args[i]);
			}
		}
		else
		{
			value = get_value(args[i]);
			lst = ft_lstnew(new_node(key, value));
			ft_lstadd_back(env, lst);
			var = lst->content;
			if (value)
				var->flag = 1;
			else
				var->flag = 2;
			free(value);
		}
		free(key);
		i++;
	}
}

void	del_content(void *content)
{
	t_env	*var;

	var = content;
	free(var->value);
	free(var->key);
	free(content);
}

void	del_var(t_list **env, char *key)
{
	t_list	*lst;
	t_list	*prev;
	t_env	*var;

	lst = *env;
	var = lst->content;
	if (!ft_strcmp(var->key, key))
	{
		*env = lst->next;
		ft_lstdelone(lst, del_content);
		return ;
	}
	while (lst->next)
	{
		prev = lst;
		lst = lst->next;
		var = lst->content;
		if (!ft_strcmp(var->key, key))
		{
			prev->next = lst->next;
			ft_lstdelone(lst, del_content);
//			free(var->value);
//			free(var->key);
//			free(lst);
			return ;
		}
	}
}

void	ft_unset(t_list **env, char **args, int fd)
{
	int 	i;
	char 	*key;

	if (!args)
	{
		ft_putstr_fd("unset: not enough arguments\n", fd);
		return ;
	}
	i = 0;
	while (args[i])
	{
		key = get_key(args[i]);
		del_var(env, key);
		free(key);
	}
}




