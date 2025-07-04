/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:36:00 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:59:15 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_cd_error_msg(t_app *app, char *path, char *error_msg)
{
	char	*temp;
	char	*final_msg;

	temp = ft_strjoin("cd: ", path, &app->curr_gc);
	if (!temp)
		cleanup_and_exit(app, EXIT_FAILURE);
	final_msg = ft_strjoin(temp, error_msg, &app->curr_gc);
	if (!final_msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (final_msg);
}

int	check_dir(t_app *app, char *path)
{
	struct stat	path_info;
	char		*msg;

	if (access(path, F_OK) == -1)
	{
		msg = build_cd_error_msg(app, path, ": No such file or directory\n");
		if (msg)
			print_error(app, msg, "1");
		return (0);
	}
	if (stat(path, &path_info) == 0 && !S_ISDIR(path_info.st_mode))
	{
		msg = build_cd_error_msg(app, path, ": Not a directory\n");
		if (msg)
			print_error(app, msg, "1");
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		msg = build_cd_error_msg(app, path, ": Permission denied\n");
		if (msg)
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
		if (!msg)
			cleanup_and_exit(app, EXIT_FAILURE);
		msg = ft_strjoin(msg, " :", &app->curr_gc);
		if (!msg)
			cleanup_and_exit(app, EXIT_FAILURE);
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
	char	*res;

	cwd = getcwd(cwd_buf, sizeof(cwd_buf));
	if (!cwd)
		return (0);
	res = ft_strdup(cwd, &app->curr_gc);
	if (!res)
		cleanup_and_exit(app, EXIT_FAILURE);
	set_env_value(app, "OLDPWD", res);
	return (1);
}
