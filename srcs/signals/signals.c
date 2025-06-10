/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:22:18 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/10 17:24:56 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigs_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
}

void	handle_SIGQUIT(void)
{
	struct sigaction	act;
	struct sigaction	old_act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = &sigs_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGQUIT, NULL, &old_act); // Todo: check returns
}

void	init_signals(void)
{
	handle_SIGQUIT();
}
