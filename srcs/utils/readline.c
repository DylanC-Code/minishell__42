/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:29:13 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 10:29:48 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_readline(t_garbage **gc, const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line)
	{
		add_to_gc(gc, line);
		return (line);
	}
	return (NULL);
}
