/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:09:37 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/23 11:40:14 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buitin_echo(t_app *app, char *str, int new_line)
{
	write(1, str, ft_strlen(str));
	if (new_line == 1)
		writet(1, "\n", 1);
}
