/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:36:00 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:38:02 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(t_app *app, char *path)
{
	struct stat	path_info;

	if (access(path, F_OK) == -1)
		return (print_error(app, ft_strjoin(ft_strjoin("cd: ", path,
						&app->curr_gc), ": No such file or directory\n",
					&app->curr_gc), "1"), 0);
	if (stat(path, &path_info) == 0 && !S_ISDIR(path_info.st_mode))
		return (print_error(app, ft_strjoin(ft_strjoin("cd: ", path,
						&app->curr_gc), ": Not a directory\n", &app->curr_gc),
				"1"), 0);
	if (access(path, X_OK) == -1)
		return (print_error(app, ft_strjoin(ft_strjoin("cd: ", path,
						&app->curr_gc), ": Permission denied\n", &app->curr_gc),
				"1"), 0);
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
