/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:42:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/12 15:39:48 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_back(t_env **env_list, t_env *new_env);

void	init_env(t_app *app, char *envp[])
{
	char	*p_delimiter;
	t_env	*new_env;

	while (envp && *envp)
	{
		new_env = gc_malloc(sizeof(t_env), &app->garb_head);
		p_delimiter = ft_strchr(*envp, '=');
		new_env->key = ft_strndup(*envp, p_delimiter - *envp);
		if (!new_env->key)
			exit_with_error("malloc", &app->garb_head);
		add_to_gc(&app->garb_head, new_env->key);
		new_env->value = ft_strdup(p_delimiter + 1);
		if (!new_env->value)
			exit_with_error("malloc", &app->garb_head);
		add_to_gc(&app->garb_head, new_env->value);
		add_env_back(&app->env_head, new_env);
		envp++;
	}
}

static void	add_env_back(t_env **env_list, t_env *new_env)
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
