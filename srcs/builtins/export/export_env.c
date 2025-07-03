/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:44:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:44:22 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *key, char *value, t_app *app)
{
	t_env	*new_node;

	if (!key)
		return (NULL);
	new_node = gc_malloc(sizeof(t_env), &app->app_gc);
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key, &app->app_gc);
	new_node->value = ft_strdup(value, &app->app_gc);
	if (!new_node->value)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

int	add_env_var(t_env **env_head, char *key, char *value, t_app *app)
{
	t_env	*current;
	t_env	*new_node;

	if (!key)
		return (0);
	current = *env_head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = ft_strdup(value, &app->app_gc);
			if (!current->value)
				return (0);
			return (1);
		}
		current = current->next;
	}
	new_node = create_env_node(key, value, app);
	if (!new_node)
		return (0);
	new_node->next = *env_head;
	*env_head = new_node;
	return (1);
}

void	export_error(t_app *app, char *key)
{
	char	*res;

	res = ft_strjoin("export: `", key, &app->curr_gc);
	if (!res)
		cleanup_and_exit(app, EXIT_FAILURE);
	res = ft_strjoin(res, "': not a valid identifier\n", &app->curr_gc);
	if (!res)
		cleanup_and_exit(app, EXIT_FAILURE);
	print_error(app, res, "1");
}
