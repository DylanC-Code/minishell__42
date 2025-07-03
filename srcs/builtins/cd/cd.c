/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:35:34 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:35:38 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(t_app *app)
{
	char	*home;

	home = get_env_value(app->env_head, "HOME");
	if (!change_dir(app, home))
		set_env_value(app, "?", "1");
	else
		set_env_value(app, "?", "0");
}

void	cd_builtin(t_app *app, char **args)
{
	char	*dir;

	if (!args || !*args)
		return (cd_home(app));
	if (!check_args(app, args))
		return ;
	dir = get_cd_dir(app, args);
	if (!dir || !check_dir(app, dir) || !update_oldpwd(app) || !change_dir(app,
			dir))
		return (set_env_value(app, "?", "1"));
	set_env_value(app, "?", "0");
}
