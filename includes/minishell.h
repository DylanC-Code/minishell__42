/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/20 14:53:50 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "input.h"
# include "libft.h"
# include "memory.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

// # define USER_PROMPT "\e[1;32mminishell\e[0m:\e[1;34m\w\e[0m$"

# define PS2_PROMPT "> "
# define OPERATORS "<>|&()"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_app
{
	t_env			*env_head;
	t_garbage		*garb_head;
}					t_app;

/* Builtins */
void				builtin_env(t_app *app);
void				builtin_exit(t_app *app, int status);

/* Init */
void				init(t_app *app, char *envp[]);
void				init_env(t_app *app, char *envp[]);
void				init_signals(void);

/* Utils */
void				exit_with_error(char *msg, t_garbage **garbage_list);
void				display_tokens(t_token *head, char *input);
t_status			print_syntax_error(const char *token);
t_status			print_unexpected_eof(char quote_type);
void				print_banner(void);

#endif
