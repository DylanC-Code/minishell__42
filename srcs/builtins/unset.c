/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:08:38 by saal-kur          #+#    #+#             */
/*   Updated: 2025/07/01 11:24:04 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_app *app, const char *key)
{
	t_env	*prev;
	t_env	*env;

	prev = NULL;
	env = app->env_head;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				app->env_head = env->next;
			break ;
		}
		prev = env;
		env = env->next;
	}
}

void	unset_builtin(t_app *app, char **args)
{
	if (!args || !*args)
		return ;
	while (*args)
	{
		remove_env_var(app, *args);
		args++;
	}
	set_env_value(app, "?", "0");
}
