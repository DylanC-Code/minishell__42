/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:22:18 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/29 11:10:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_code = 0;

void	sigs_handler(int sig_code)
{
	if (sig_code == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line(NULL, 0);
		rl_on_new_line();
		rl_redisplay();

		g_sig_code = SIGINT;
	}
	else if (sig_code == SIGQUIT)
		g_sig_code = SIGQUIT;
	else
		sig_code = 0;
}

void	init_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = &sigs_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}
