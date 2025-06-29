/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 23:00:58 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/29 10:51:21 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_value(t_app *app, const char *key, const char *value)
{
	t_env	*tmp;

	tmp = app->env_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(value, &app->app_gc);
			return ;
		}
		tmp = tmp->next;
	}
	add_env_node(app, key, value);
}

void	add_env_node(t_app *app, const char *key, const char *value)
{
	t_env	*new_env;

	new_env = gc_malloc(sizeof(t_env), &app->app_gc);
	if (!new_env)
		cleanup_and_exit(app, EXIT_FAILURE);
	new_env->key = ft_strdup(key, &app->app_gc);
	if (!new_env->key)
		cleanup_and_exit(app, EXIT_FAILURE);
	new_env->value = ft_strdup(value, &app->app_gc);
	if (!new_env->value)
		cleanup_and_exit(app, EXIT_FAILURE);
	new_env->next = NULL;
	add_env_back(&app->env_head, new_env);
}

void	add_env_back(t_env **env_list, t_env *new_env)
{
	t_env	*next;

	if (!*env_list)
	{
		*env_list = new_env;
		return ;
	}
	next = *env_list;
	while (next->next)
		next = next->next;
	next->next = new_env;
}
