/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saal-kur <saal-kur@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-25 10:08:38 by saal-kur          #+#    #+#             */
/*   Updated: 2025-06-25 10:08:38 by saal-kur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char *env_key, t_app *app)
{
	t_env	*curr;

	if(!*env_key || !env_key)
		return (0);
	curr = app->env_head;
	while (curr)
	{
		if (ft_strcmp(env_key, curr->key) == 0)
		{
			curr->value = ft_strdup("", &app->app_gc);
			return (0);
		}
		curr = curr->next;
	}
	return (0);
}