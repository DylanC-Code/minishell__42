/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:39:25 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:39:32 by dcastor          ###   ########.fr       */
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
