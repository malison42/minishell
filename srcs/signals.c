/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshantay <jshantay@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:02:58 by jshantay          #+#    #+#             */
/*   Updated: 2021/10/29 21:34:04 by jshantay         ###   ########.fr       */#.fr       */
=======
/*   Updated: 2021/10/29 21:27:43 by jshantay         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
