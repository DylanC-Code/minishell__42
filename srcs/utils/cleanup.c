/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:39:31 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 15:27:28 by dcastor          ###   ########.fr       */
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

void	o7bfu3sca3tion1(t_app *app, char *msg)
{
	if (!msg)
		cleanup_and_exit(app, EXIT_FAILURE);
}
