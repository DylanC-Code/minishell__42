/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:48:22 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 14:01:36 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_env_node(t_app *app, const char *key, const char *value);

static char	*build_env_line(t_env *node, t_garbage **gc)
{
	char	*line;
	size_t	len;

	len = ft_strlen(node->key) + 1 + ft_strlen(node->value);
	line = gc_malloc(len + 1, gc);
	if (!line)
		return (NULL);
	ft_strlcpy(line, node->key, len);
	ft_strlcat(line, "=", len);
	ft_strlcat(line, node->value, len);
	return (line);
}

char	**env_list_to_envp(t_env *env_list, t_garbage **gc)
{
	char	**envp;
	int		count;
	int		i;
	t_env	*tmp;

	count = 0;
	tmp = env_list;
	while (tmp && ++count)
		tmp = tmp->next;
	envp = gc_malloc(sizeof(char *) * (count + 1), gc);
	if (!envp)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		envp[i++] = build_env_line(tmp, gc);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env_value(t_env *env_list, const char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env_value(t_app *app, const char *key, const char *value)
{
	t_env	*tmp;

	tmp = app->env_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(value);
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
		return ;
	new_env->key = ft_strdup(key);
	if (!new_env->key)
		return ;
	new_env->value = ft_strdup(value);
	if (!new_env->value)
		return ;
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
