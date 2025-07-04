/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:20:49 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:24:23 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_env_start(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| c == '?');
}

int	valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}
int	find_quote_end(char *s, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (s[i] && s[i] != quote_char)
		i++;
	return (i);
}

int	find_var_end(char *str, int start)
{
	int	i;

	i = start;
	if (str[i] == '?')
		return (i + 1);
	while (str[i] && valid_var_char(str[i]))
		i++;
	return (i);
}
