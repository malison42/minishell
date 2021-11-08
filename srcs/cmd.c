/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:27:43 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/08 16:33:03 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*refactor_pipe(char *cmds)
{
	int		i;
	int		quote;
	char	*tmp;

	quote = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmds) + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (cmds[i])
	{
		if ((cmds[i] == '"' || cmds[i] == 39) && quote == 0)
			quote = 1;
		else if ((cmds[i] == '"' || cmds[i] == 39) && quote == 1)
			quote = 0;
		if (cmds[i] == 124 && quote == 0)
			tmp[i++] = -1;
		tmp[i] = cmds[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	free_cmd(char **cmds, char **line)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (cmds[i])
			free(cmds[i++]);
		free(cmds);
	}
	cmds = NULL;
	free(line);
	line = NULL;
}

void	cmd_parse(t_cmd *new, char *s, t_list *env, t_prs *prs)
{
	while (s[prs->i])
	{
		while (s[prs->i] == ' ')
			prs->i++;
		if (s[prs->i] == '<' || s[prs->i] == '>')
			new->redir = redir(new->redir, s, env, prs);
		while (s[prs->i] && s[prs->i] != ' '
			   && s[prs->i] != '>' && s[prs->i] != '<')
			get_arg(new, s, env, prs);
	}
}

t_cmd	*new_cmd(char *s, t_list *env)
{
	/*здесь начинается магия парсинга команд*/
	t_prs	prs;
	t_cmd	*new;
	int		i;

	init_prs_cmd(&prs);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	init_cmd(new, s, env);
	cmd_parse(new, s, env, &prs);
	new->cmd = new->args[0];
	i = get_size(s);
	i += count_extra_args(s, 0, 0, env);
	while (i >= prs.arg_num)
	{
		free(new->args[i]);
		new->args[i] = NULL;
		i--;
	}
	if (prs.ambiguous == 1)
		new->cmd = NULL;
	return (new);
}

t_list	*get_cmd(t_list *cmd, char *line, t_list *env)
{
	/*
	 * получаем команды и парсим их на сами команды
	 * и аргументы и редиректы
	 */
	char	**cmds;
	t_cmd	*tmp;
	t_list	*new;
	int		i;

	i = 0;
	cmds = ft_split(refactor_pipe(line), -1);
	if (!cmds)
	{
		ft_putendl_fd("Error: split", 2);
		exit(EXIT_FAILURE);
	}
	while (cmds[i])
	{
		tmp = new_cmd(cmds[i], env);
		new = ft_lstnew(tmp);
		ft_lstadd_back(&cmd, new);
		i++;
	}
	free_cmd(cmds, &line);
	return (cmd);
}