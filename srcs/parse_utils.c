
#include "../inc/minishell.h"

int	skip_space_and_redir(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	while (s[i] == '>' || s[i] == '<')
	{
		i++;
		while (s[i] == ' ')
			i++;
		while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
			i++;
	}
	return (i);
}

int	check_for_quote(char c, int quote)
{
	if (c == '"' && quote == 0)
		quote = 2;
	else if (c == '\'' && quote == 0)
		quote = 1;
	else if ((c == '"' && quote == 2) || (c == '\'' && quote == 1))
		quote = 0;
	return (quote);
}

int	skip_quotes(char *str, int i)
{
	if (str[i] == '"')
	{
		while (str[i] && str[i] != '"')
			i++;
	}
	if (str[i] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i + 1);
}

int	redir_syntax_err(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		i += 2;
	else
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (!str[i])
			ft_putendl_fd
					("minishell: syntax error near unexpected token `newline'", 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putchar_fd(str[i], 2);
			ft_putendl_fd("'", 2);
		}
		return (-100);
	}
	return (i);
}