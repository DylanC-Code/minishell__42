/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:42:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 13:59:01 by dcastor          ###   ########.fr       */
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
		ft_bzero(new_env, sizeof(t_env));
		p_delimiter = ft_strchr(*envp, '=');
		new_env->key = ft_strndup(*envp, p_delimiter - *envp);
		if (!new_env->key)
			exit_with_error("malloc", &app->app_gc);
		add_to_gc(&app->app_gc, new_env->key);
		new_env->value = ft_strdup(p_delimiter + 1);
		if (!new_env->value)
			exit_with_error("malloc", &app->app_gc);
		add_to_gc(&app->app_gc, new_env->value);
		add_env_back(&app->env_head, new_env);
		envp++;
	}
}
