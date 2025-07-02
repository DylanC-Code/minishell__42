/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:20:49 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/29 16:51:37 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_env_start(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| c == '?' || c == '$');
}

int	valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}

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

int	find_quote_end(char *s, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (s[i] && s[i] != quote_char)
		i++;
	return (i);
}

int	contains_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
