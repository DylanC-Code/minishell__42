/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:30:54 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/25 15:56:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_app *app, char **args)
{
	t_env	*next;

	(void)args;
	next = app->env_head;
	if (!next)
		return ;
	while (next)
	{
		printf("%s=%s\n", next->key, next->value);
		next = next->next;
	}
}
