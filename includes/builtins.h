/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:40:06 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:45:47 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "init.h"
# include "input.h"
# include "minishell.h"

void	env_builtin(t_app *app, char **args);
void	exit_builtin(t_app *app, char **args);
void	cd_builtin(t_app *app, char **args);
void	echo_builtin(t_app *app, char **args);
void	export_builtin(t_app *app, char **args);
void	pwd_builtin(t_app *app, char **args);
void	unset_builtin(t_app *app, char **args);

/* Export */
int		check_varname_syntax(char *arg);
char	*get_varname_value(char *arg);
char	*get_varname_key(char *arg, t_app *app);
t_env	*create_env_node(char *key, char *value, t_app *app);
int		add_env_var(t_env **env_head, char *key, char *value, t_app *app);
void	export_error(t_app *app, char *key);

#endif
