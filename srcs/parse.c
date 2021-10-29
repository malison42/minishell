/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:09:55 by jshantay          #+#    #+#             */
/*   Updated: 2021/10/29 14:29:40 by jshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_redir(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i);
		while (str[i] == ' ')
			i++;
		if (str[i] == '>' || str[i] == '<')
			i = redir_syntax_err(str, i);
		if (i == -100)
			return (1);
		i++;
	}
	return (0);
}

static int	check_quote(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] != '"')
				return (err_msg("minishell: unclosed double quote error"));
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] != '\'')
				return (err_msg("minishell: unclosed single quote error"));
		}
		i++;
	}
	return (0);
}

static int	check_pipe_err(char *s)
{
	int		i;
	int		quote;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			quote = check_for_quote(s[i++], quote);
		if (s[i] == '|' && !quote)
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '|')
				return (err_msg
						("minishell: syntax error near unexpected token `|'"));
		}
		i++;
	}
	return (0);
}

int	parse(char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, " ");
	if (check_pipe_err(trim_line) || check_quote(trim_line)
		|| check_redir(trim_line))
	{
		free(trim_line);
		return (1);
	}
	if (trim_line[ft_strlen(trim_line) - 1] == '|')
	{
		free(trim_line);
		return (err_msg("minishell: syntax error near "
						"unexpected token `newline'"));
	}
	free(trim_line);
	return (0);
}