/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:45:15 by jshantay          #+#    #+#             */
/*   Updated: 2021/10/29 21:36:17 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_err
{
	int		err_id;
	char	*err_msg;
} t_err;

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	t_list	*redir;
}	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_mshl
{
	t_list	*env;
	t_err	err;
}	t_mshl;

void	save_env(t_list **env, char **envp);
t_env	*new_env(char *key, char *value);
t_env	*new_node(char *key, char *value);
char	*get_value(char *s);
char	*get_key(char *s);
int		parse(char *line);

int		check_for_quote(char c, int quote);
int		skip_quotes(char *str, int i);
int		redir_syntax_err(char *str, int i);
t_list	*cmd_parse(t_list *cmd, char *line, t_list *env);

void	ft_handler(int signum);

void	free_env(t_list *env);

int		err_msg(char *err);

#endif