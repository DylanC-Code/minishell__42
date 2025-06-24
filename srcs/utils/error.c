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

