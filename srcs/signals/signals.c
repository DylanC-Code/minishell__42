/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:22:18 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:18:42 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_in_heredoc = 0;

void	sigs_handler(int signal)
{
	if (signal == SIGINT && !g_in_heredoc)
		write(STDOUT_FILENO, "\n" PS2_PROMPT, ft_strlen(PS2_PROMPT) + 1);
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
