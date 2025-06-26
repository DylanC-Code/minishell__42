/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 17:19:45 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "executor.h"
# include "init.h"
# include "input.h"
# include "libft.h"
# include "memory.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PS2_PROMPT MAGENTA "> " RESET
# define PS3_PROMPT CYAN ">> " RESET
# define OPERATORS "<>|&()"

/* Builtins */
void							env_builtin(t_app *app, char **args);
void							exit_builtin(t_app *app, char **args);
void							cd_builtin(t_app *app, char **args);
void							echo_builtin(t_app *app, char **args);
void							export_builtin(t_app *app, char **args);
void							pwd_builtin(t_app *app, char **args);
void							unset_builtin(t_app *app, char **args);

/* Init */
void							init(t_app *app, char *envp[]);
void							init_env(t_app *app, char *envp[]);
void							init_signals(void);

/* Utils */
void							exit_with_error(t_app *app, char *msg);
void							display_tokens(t_token *head, char *input);
void							print_banner(void);
char							**env_list_to_envp(t_env *env_list,
									t_garbage **gc);
void							safe_close(int *fd);
char							*get_env_value(t_env *env_list,
									const char *key);
void							add_env_back(t_env **env_list, t_env *new_env);
void							set_env_value(t_app *app, const char *key,
									const char *value);
void							cleanup(t_app *app);
void							cleanup_and_exit(t_app *app, int status);
char							*gc_readline(t_app *app, const char *prompt);
void							print_error(t_app *app, char *msg,
									char *error_code);

extern volatile sig_atomic_t	in_heredoc;

#endif
