/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:55:49 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 09:39:08 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_app *app, char *msg, char *error_code)
{
	char	*res;
	
	set_env_value(app, "?", error_code);
	res = ft_strjoin("minishell: ", msg, &app->curr_gc);
	if (!res)
		cleanup_and_exit(app);
	ft_putstr_fd(res, STDERR_FILENO);

}

void	exit_with_error(char *msg, t_garbage **garbage_list)
{
	perror(msg);
	gc_cleanup(garbage_list);
	exit(EXIT_FAILURE); // TODO: adapt status number
}

t_status	print_syntax_error(const char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (ERROR);
}

t_status	print_unexpected_eof(char quote_type)
{
	printf("minishell: unexpected EOF while looking for matching `%c'\n",
		quote_type);
	return (ERROR);
}

