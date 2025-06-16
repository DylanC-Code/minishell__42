/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:55:49 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 16:04:09 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_error(char *msg, t_garbage **garbage_list)
{
	perror(msg);
	gc_cleanup(garbage_list);
	exit(EXIT_FAILURE); // TODO: adapt status number
}

t_parse_status	print_syntax_error(const char *token)
{
	printf("minishell: syntax error near unexpected token `%s\n", token);
	return (CMD_INVALID);
}

t_parse_status	print_op_start_syntax_error(const char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (line[0] == '|' && line[1] == '|')
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	else if (line[0] == '&' && line[1] == '&')
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
	else if (line[0] == '|')
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (line[0] == '&')
		ft_putstr_fd("minishell: syntax error near unexpected token `&'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	return (CMD_INVALID);
}
