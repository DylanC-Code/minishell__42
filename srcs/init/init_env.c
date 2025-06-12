/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:42:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/12 11:50:36 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_app *app, char *envp[])
{
	t_env	*new_env;

	while (envp && *envp)
	{
		new_env = gc_malloc(sizeof(t_env), &app->garb_head);
		// printf("env\n");
		envp++;
	}
}

// static void	add_env_back(t_env **env_list, char)
