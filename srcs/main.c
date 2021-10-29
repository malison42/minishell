/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:26:01 by jshantay          #+#    #+#             */
/*   Updated: 2021/10/29 16:02:50 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	err_msg(char *err)
{
	if (err)
		ft_putendl_fd(err, 2);
	return (1);
}

void	read_line(char **line, t_list *env)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	*line = readline("\033[32mminishell$ \033[90m\033[0m");
	if (*line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_env(env);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(*line, ""))
		add_history(*line);
}

void	loop(t_mshl *data)
{
	char	*line;
	t_list	*tmp;
	t_list	*cmd;

	while (1)
	{
		read_line(&line, data->env);
		tmp = data->env;
		if (line != NULL && !parse(line))
		{
			cmd = cmd_parse(cmd, line, tmp);
//			exec();
		}
		free(line);
//		free_cmd(cmd);
	}
}

int main(void)
{
	t_mshl data;
	extern char	**environ;

	save_env(&(data.env), environ);
	loop(&data);
	return (0);
}
