/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:09:37 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/25 15:45:34 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_app *app, char *str, int new_line)
{
	write(1, str, ft_strlen(str));
	if (new_line == 1)
		write(1, "\n", 1);
}
