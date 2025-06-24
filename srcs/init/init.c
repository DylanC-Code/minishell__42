/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:39:45 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 15:31:27 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_app *app, char *envp[])
{
	(void)envp;
	print_banner();
	ft_bzero(app, sizeof(t_app));
	init_env(app, envp);
	init_signals();
}
