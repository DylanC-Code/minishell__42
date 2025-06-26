/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:26:36 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/27 10:14:06 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_builtin(t_app *app, char **args)
{
	if (*(args + 1) != NULL)
		print_error(app, "cd: too many arguments\n", "1");
	else if (access(*args, R_OK) == -1)
	{
		perror("cd");
		cleanup_and_exit(app, errno);
	}
	else if (access(*args, F_OK) == -1)
	{
		perror("cd");
		cleanup_and_exit(app, errno);
	}
}
