/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/07 11:06:20 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "colors.h"
# include "executor.h"
# include "expansion.h"
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

# define PS2_PROMPT "\001\033[0;35m\002> \001\033[0m\002"
# define PS3_PROMPT "\001\033[0;36m\002>> \001\033[0m\002"
# define OPERATORS "<>|&()"
# define PWD_BUFFER_SIZE 50000

/* Init */
void							init(t_app *app, char *envp[]);
void							init_env(t_app *app, char *envp[]);
void							init_signals(void);

/* Utils */
void							exit_with_error(t_app *app, char *msg);
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
void							add_env_node(t_app *app, const char *key,
									const char *value);
int								change_dir(t_app *app, char *path);
t_cmd_sequence					*parse_tokens(t_token *head, t_garbage **gc,
									t_app *app);
void							o7bfu3sca3tion1(t_app *app, char *msg);

extern volatile sig_atomic_t	g_in_heredoc;

#endif
