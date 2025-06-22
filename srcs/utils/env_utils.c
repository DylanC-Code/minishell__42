/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:48:22 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/21 09:54:09 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
