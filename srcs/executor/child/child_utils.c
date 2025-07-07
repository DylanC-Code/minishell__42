/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:01:28 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/07 10:42:44 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_path(t_app *app, char *dir, char *cmd)
{
	char	*path;

	path = ft_strjoin(dir, "/", &app->curr_gc);
	if (!path)
		return (NULL);
	path = ft_strjoin(path, cmd, &app->curr_gc);
	return (path);
}

char	*find_in_path(t_app *app, char *cmd)
{
	char	*env_path;
	char	**paths;
	char	*result;
	int		i;

	env_path = get_env_value(app->env_head, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':', &app->curr_gc);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		result = build_path(app, paths[i], cmd);
		if (!result)
			return (NULL);
		if (access(result, X_OK) == 0)
			return (result);
		if (errno == 13)
			exit_with_error(app, result);
		i++;
	}
	return (NULL);
}

void	sanitize_stdin(t_app *app)
{
	int	nullfd;

	nullfd = open("/dev/null", O_RDONLY);
	if (nullfd < 0)
		exit_with_error(app, "open");
	if (dup2(nullfd, STDIN_FILENO) == -1)
		exit_with_error(app, "dup2");
	close(nullfd);
}
