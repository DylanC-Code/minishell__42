/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/12 15:59:55 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# define USER_PROMPT "minishell>"

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_garbage
{
	void				*alloc;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_app
{
	t_env				*env_head;
	t_garbage			*garb_head;
}						t_app;

/* Builtins */
void					builtin_env(t_app *app);
void					builtin_exit(t_app *app, int status);

/* Init */
void					init(t_app *app, char *envp[]);
void					init_env(t_app *app, char *envp[]);
void					init_signals(void);

/* Memory */
void					*gc_malloc(size_t size, t_garbage **garbage_list);
void					add_to_gc(t_garbage **garbage_list, void *alloc);
void					gc_cleanup(t_garbage **garbage_list);

/* Utils */
void					exit_with_error(char *msg, t_garbage **garbage_list);

#endif
