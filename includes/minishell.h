/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 15:10:30 by dcastor          ###   ########.fr       */
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
void		builtin_env(t_app *app);
void		builtin_exit(t_app *app, int status);

/* Init */
void		init(t_app *app, char *envp[]);
void		init_env(t_app *app, char *envp[]);
void		init_signals(void);

/* Utils */
void		exit_with_error(char *msg, t_garbage **garbage_list);
void		display_tokens(t_token *head, char *input);
t_status	print_syntax_error(const char *token);
t_status	print_unexpected_eof(char quote_type);
void		print_banner(void);
char		**env_list_to_envp(t_env *env_list, t_garbage **gc);
void		safe_close(int *fd);
char		*get_env_value(t_env *env_list, const char *key);
void		add_env_back(t_env **env_list, t_env *new_env);
void		set_env_value(t_app *app, const char *key, const char *value);
void		cleanup(t_app *app);
char		*gc_readline(t_garbage **gc, const char *prompt);

#endif
