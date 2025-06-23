/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:18:35 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/23 11:42:25 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtin_pwd(t_app *app, char *buf, size_t size)
{
	if (!getcwd(buf, size))
		return (NULL);
	return (buf);
}
