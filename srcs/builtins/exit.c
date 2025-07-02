/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:56:46 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/01 10:39:17 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	non_numeric_arg_error(t_app *app, char *arg);

void	exit_builtin(t_app *app, char **args)
{
	char	status_code;

	status_code = ft_atoi(get_env_value(app->env_head, "?"));
	printf("exit\n");
	if (!args || !*args)
		cleanup_and_exit(app, status_code);
	if (!is_valid_number(*args))
		non_numeric_arg_error(app, *args);
	else if (args[1])
		return (print_error(app, "exit:  too many arguments\n", "1"));
	status_code = ft_atoi(*args);
	cleanup_and_exit(app, status_code);
}

static void	non_numeric_arg_error(t_app *app, char *arg)
{
	char	*msg;

	msg = ft_strjoin("exit: ", arg, &app->app_gc);
	if (!msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	msg = ft_strjoin(msg, ": numeric argument required\n", &app->app_gc);
	if (!msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	print_error(app, msg, "2");
	cleanup_and_exit(app, 2);
}
