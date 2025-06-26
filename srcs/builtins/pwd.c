/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:18:35 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/26 17:16:15 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_app *app, char **args)
{
	(void)app;
	(void)args;
	printf("PWD BUILTIN NOT DONE!\n");
	// if (!getcwd(buf, size))
	// 	return (NULL);
	// return (buf);
}
