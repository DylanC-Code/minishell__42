/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:42:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/29 11:00:18 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_app *app, char *envp[])
{
	char	*p_delimiter;
	t_env	*new_env;

	while (envp && *envp)
	{
		new_env = gc_malloc(sizeof(t_env), &app->app_gc);
		if (!new_env)
			cleanup_and_exit(app, EXIT_FAILURE);
		p_delimiter = ft_strchr(*envp, '=');
		new_env->key = ft_strndup(*envp, p_delimiter - *envp, &app->app_gc);
		if (!new_env->key)
			cleanup_and_exit(app, EXIT_FAILURE);
		new_env->value = ft_strdup(p_delimiter + 1, &app->app_gc);
		if (!new_env->value)
			cleanup_and_exit(app, EXIT_FAILURE);
		add_env_back(&app->env_head, new_env);
		envp++;
	}
}
