/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:23:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/29 16:31:24 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "init.h"
# include "input.h"
# include "minishell.h"

int		valid_var_char(char c);
char	*look_up_env(char *var_name, t_env *env);
int		valid_env_start(char c);
int		find_quote_end(char *s, int start, char quote_char);
int		contains_quotes(char *s);
char	*process_mixed_quotes(char *arg, t_app *app);
char	*process_variable_expansion(char *section, t_app *app);
char	*process_section_literal(char *s, int start, int end, t_app *app);
char	*process_section_expand(char *s, int start, int end, t_app *app);
char	*process_argument(char *arg, t_app *app);

typedef struct s_text_range
{
	int start;
	int end;
} t_text_range;

#endif
