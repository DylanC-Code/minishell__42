/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:18:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 16:05:11 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unexpected_token_error(t_app *app, char *token_value)
{
	char	*msg;

	msg = ft_strjoin("syntax error near unexpected token `", token_value,
			&app->curr_gc);
	if (!msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	msg = ft_strjoin(msg, "'\n", &app->curr_gc);
	if (!msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	print_error(app, msg, "2");
}

void	unexpected_eof_error(t_app *app, char *quote_type)
{
	char	*msg;

	msg = ft_strjoin("unexpected EOF while looking for matching `", quote_type,
			&app->curr_gc);
	if (!msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	msg = ft_strjoin(msg, "'\n", &app->curr_gc);
	if (!msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	print_error(app, msg, "2");
}
