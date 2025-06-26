/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:56:46 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 17:13:49 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_app *app, char **args)
{
	printf("EXIT BUILTIN NOT DONE!\n");
	(void)args;
	gc_cleanup(&app->app_gc);
	// exit(status);
}
