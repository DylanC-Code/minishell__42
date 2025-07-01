/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:18:35 by saal-kur          #+#    #+#             */
/*   Updated: 2025/07/01 14:05:41 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_app *app, char **args)
{
	char	buffer[PWD_BUFFER_SIZE];

	(void)args;
	if (!getcwd(buffer, PWD_BUFFER_SIZE))
	{
		return print_error(app,
							"pwd: error retrieving current directory: \
getcwd: cannot access parent directories: \
No such file or directory\n",
							"1");
	}
	else if (access(buffer, F_OK) == -1)
		print_error(app,
					"pwd: error retrieving current directory: \
	getcwd: cannot access parent directories: No such file or directory\n",
					"1");
	printf("%s\n", buffer);
	set_env_value(app, "?", "0");
}
