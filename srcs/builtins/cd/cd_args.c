/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:34:59 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:35:04 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(t_app *app, char **args)
{
	if (*(args + 1) != NULL)
	{
		print_error(app, "cd: too many arguments\n", "1");
		return (0);
	}
	return (1);
}

static char	*get_home(t_app *app)
{
	char	*home;

	home = get_env_value(app->env_head, "HOME");
	if (!home || !*home)
		return (print_error(app, "cd: HOME not set\n", "1"), NULL);
	return (home);
}

static char	*get_oldpwd(t_app *app)
{
	char	*old_pwd;

	old_pwd = get_env_value(app->env_head, "OLDPWD");
	if (!old_pwd || !*old_pwd)
	{
		print_error(app, "cd: OLDPWD not set\n", "1");
		return (NULL);
	}
	ft_putstr_fd(old_pwd, 1);
	ft_putchar_fd('\n', 1);
	return (old_pwd);
}

char	*get_cd_dir(t_app *app, char **args)
{
	if (!*args)
		return (get_home(app));
	if (ft_strcmp(args[0], "-") == 0)
		return (get_oldpwd(app));
	return (*args);
}
