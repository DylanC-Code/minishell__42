/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:05:19 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/25 10:07:09 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_first_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	valid_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}

int	check_varname_syntax(char *arg)
{
	int	i;

	i = 0;
	if (!valid_first_char(arg[i]))
		return (0);
	while (arg[i] && valid_char(arg[i]))
		i++;
	if (arg[i] != '=' && arg[i] != 0)
		return (0);
	return (1);
}

char	*get_varname_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] != '=')
		return (NULL);
	return (arg + (i + 1));
}

char	*get_varname_key(char *arg, t_app *app)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_strndup(arg, i, &app->app_gc));
}

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

int	export(t_app *app, char **args)
{
	int	i;
	int	ret_val;

	ret_val = 0;
	i = 0;
	while (args[i])
	{
		if (!check_varname_syntax(args[i]))
			ret_val = 1;
		else
			ret_val = add_env_var(&app->env_head, get_varname_key(args[i], app),
					get_varname_value(args[i]), app);
		i++;
	}
	return (ret_val);
}
