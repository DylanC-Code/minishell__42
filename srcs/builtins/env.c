/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:30:54 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/12 15:34:59 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_app *app)
{
	t_env	*next;

	next = app->env_head;
	if (!next)
		return ;
	while (next)
	{
		printf("%s=%s\n", next->key, next->value);
		next = next->next;
	}
}
