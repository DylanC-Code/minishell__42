/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:42:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/12 12:43:09 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s\n", new_env->key);
		envp++;
	}
}

// static void	add_env_back(t_env **env_list, char)
