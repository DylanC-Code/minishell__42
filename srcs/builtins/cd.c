/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:26:36 by saal-kur          #+#    #+#             */
/*   Updated: 2025/07/01 11:35:33 by dcastor          ###   ########.fr       */
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

char	*get_cd_dir(t_app *app, char **args)
{
	char	*home_env;
	char	*old_pwd;

	if (!*args)
	{
		home_env = get_env_value(app->env_head, "HOME");
		if (!home_env || !*home_env)
		{
			print_error(app, "cd: HOME not set\n", "1");
			return (NULL);
		}
		return (home_env);
	}
	else if (ft_strcmp(args[0], "-") == 0)
	{
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
	return (*args);
}
int	check_dir(t_app *app, char *path)
{
	struct stat	path_info;
	char		*msg;

	if (access(path, X_OK) == -1)
	{
		print_error(app, NULL, "1");
		perror("cd");
		return (0);
	}
	if (stat(path, &path_info) == 0 && !S_ISDIR(path_info.st_mode))
	{
		msg = ft_strjoin("cd: ", path, &app->curr_gc);
		msg = ft_strjoin(msg, ": Not a directory\n", &app->curr_gc);
		print_error(app, msg, "1");
		return (0);
	}
	return (1);
}

int	change_dir(t_app *app, char *path)
{
	char	*msg;

	if (chdir(path) == -1)
	{
		msg = ft_strjoin("cd : ", path, &app->curr_gc);
		msg = ft_strjoin(msg, " :", &app->curr_gc);
		print_error(app, msg, "1");
		perror("chdir");
		return (0);
	}
	return (1);
}
int	update_oldpwd(t_app *app)
{
	char	*cwd;
	char	cwd_buf[PWD_BUFFER_SIZE];

	cwd = getcwd(cwd_buf, sizeof(cwd_buf));
	if (!cwd)
		return (0);
	set_env_value(app, "OLDPWD", ft_strdup(cwd, &app->curr_gc));
	return (1);
}
static void	cd_home(t_app *app)
{
	char	*home;

	home = get_env_value(app->env_head, "HOME");
	if (!change_dir(app, home))
	{
		set_env_value(app, "?", "1");
	}
	else
		set_env_value(app, "?", "0");
}

void	cd_builtin(t_app *app, char **args)
{
	char	*dir;

	if (!args || !*args)
	{
		cd_home(app);
		return ;
	}
	if (!check_args(app, args))
		return ;
	dir = get_cd_dir(app, args);
	if (!dir || !check_dir(app, dir) || !update_oldpwd(app) || !change_dir(app,
			dir))
	{
		set_env_value(app, "?", "1");
		return ;
	}
	set_env_value(app, "?", "0");
}
