/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malison <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:48:42 by malison           #+#    #+#             */
/*   Updated: 2021/10/30 13:11:31 by malison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int re_output(char *filename, int fd0)
{
	int fd;

	if (access(filename, F_OK))
		fd = open(filename, O_WRONLY);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	printf("%d\n", fd);
	return (fd);
}

int re2_output(char *filename)
{
	int fd;

	if (!access(filename, F_OK))
		fd = open(filename, O_APPEND);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	printf("%d\n", fd);
	return (fd);
}

int re_input(char *filename)
{
	int fd;

	if (!access(filename, F_OK))
		fd = open(filename, O_RDONLY);
	else
		fd = -1;
	return (fd)
}
