/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:24:48 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:25:28 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*look_up_env(char *var_name, t_env *env)
{
	t_env	*curr_env;

	curr_env = env;
	while (curr_env)
	{
		if (ft_strcmp(curr_env->key, var_name) == 0)
			return (curr_env->value);
		curr_env = curr_env->next;
	}
	return ("");
}

char	*get_var_value(char *str, int start, int end, t_app *app)
{
	char	*var_name;
	char	*value;

	var_name = ft_strndup(str + start, end - start, &app->curr_gc);
	if (!var_name)
		cleanup_and_exit(app, EXIT_FAILURE);
	value = look_up_env(var_name, app->env_head);
	return (value);
}
