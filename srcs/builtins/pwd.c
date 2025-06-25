/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:18:35 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/25 15:47:19 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pwd_builtin(t_app *app, char *buf, size_t size)
{
	if (!getcwd(buf, size))
		return (NULL);
	return (buf);
}
