/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:55:49 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/12 11:58:00 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_error(char *msg, t_garbage **garbage_list)
{
	perror(msg);
	gc_cleanup(garbage_list);
	exit(EXIT_FAILURE); // TODO: adapt status number
}
