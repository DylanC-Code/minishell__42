/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:39:31 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/29 16:13:05 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_app *app)
{
	gc_cleanup(&app->app_gc);
	gc_cleanup(&app->curr_gc);
}

void	cleanup_and_exit(t_app *app, int status)
{
	rl_clear_history();
	cleanup(app);
	exit(status);
}
