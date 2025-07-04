/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:05:19 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/28 22:39:51 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_builtin(t_app *app, char **args)
{
	int	i;
	int	ret_val;

	i = 0;
	if (!args || !args[0])
		return (env_builtin(app, args));
	set_env_value(app, "?", "0");
	while (args[i])
	{
		if (!check_varname_syntax(args[i]))
		{
			export_error(app, get_varname_key(args[i], app));
			set_env_value(app, "?", "1");
		}
		else
		{
			ret_val = add_env_var(&app->env_head, get_varname_key(args[i], app),
				get_varname_value(args[i]), app);
			if (ret_val == -1)
				cleanup_and_exit(app, EXIT_FAILURE);
		}
		i++;
	}
}
