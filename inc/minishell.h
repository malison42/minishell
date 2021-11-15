/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:45:15 by jshantay          #+#    #+#             */
/*   Updated: 2021/11/15 17:08:57 by jshantay         ###   ########.fr       */
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

typedef struct s_tmp
{
	int i;
	char *res;
}	t_tmp;

typedef struct	s_prs
{
	int						arg_num;
	int						i;
	int						ambiguous;
	int						ret_value;
	char					**extra_args;
	int						outside_quote;
	t_tmp					tmp;
}	t_prs;

typedef struct	s_redir
{
	char					type;
	char					*file;
}	t_redir;

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
	int 	flag;
}		t_env;

typedef struct s_mshl
{
	t_list	*env;
	t_err	err;
}	t_mshl;

int	g_exit_status;

void	save_env(t_list **env, char **envp);
t_env	*new_env(char *key, char *value);
t_env	*new_node(char *key, char *value);
t_cmd	*new_cmd(char *s, t_list *env);
char	*get_value(char *s);
char	*get_key(char *s);
int		get_size(char *s);
int		parse(char *line);

int		check_for_quote(char c, int quote);
int		skip_quotes(char *str, int i);
int		skip_space_and_redir(char *s, int i);
int		redir_syntax_err(char *str, int i);


t_list	*get_cmd(char *line, t_list *env);
void	allocate_args(char *s, t_cmd *cmd, t_list *env);
int		count_extra_args(char *s, int i, int j, t_list *env);
char	*variable_expander(char *key, t_list *env);

t_list	*redir(t_list *redir, char *s, t_list *env, t_prs *prs);
t_redir	*new_redir(char *s, t_list *env, t_prs *prs);
void	get_filepath(t_redir *redir, char *s, t_list *env, t_prs *prs);
void	get_file_quote(t_redir *redir, char *s, t_list *env, t_prs *prs);
void	join_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);
int		check_ambiguous_redir(char *s, t_list *env, t_prs *prs);
char	*single_quotes(char *s, t_prs *prs);
char	*double_quotes(char *s, t_list *env, t_prs *prs);
int		ambiguous_err_msg(char *expanded, char *joined, t_prs *prs, int i);
char	*env_var_checker(char *s, t_list *env, t_prs *prs);
char	*remove_spaces(char *s);
char	*single_quotes(char *s, t_prs *prs);
char	*double_quotes(char *s, t_list *env, t_prs *prs);
void	get_dbl_quotes(t_cmd *new, char *s, t_list *env_lst, t_prs *prs);
char	*remove_spaces(char *s);
char	*get_ambiguous_var(char *joined, char *var);
int		find_end_of_var(char *s, int i);
int		is_ambiguous_var_valid(char *var, char *joined);
void	init_prs_cmd(t_prs *prs);
void	init_cmd(t_cmd *new, char *s, t_list *env);
void	get_arg(t_cmd *new, char *s, t_list *env, t_prs *prs);

void	exec(t_list *cmd, t_list *env);
void	ft_dup2(int fd1, int fd2);
void	wait_cmds(int cnt_cmd);
void	close_fd(int *fd, int nbr);
void	exec_cmd(t_list *cmds, int *fd, t_list *env, int i);
char	**list_to_arr(t_list *lst);
char	*get_cmd_path(char *cmd, char **paths);

/*BUILTIN*/

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_list *envp, int status);

/*BUILTIN*/

void	ft_handler(int signum);

void	free_env(t_list *env);
void	free_cmd_list(t_list *cmd);

int		err_msg(char *err);

#endif