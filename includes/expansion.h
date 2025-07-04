/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:23:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:42:21 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "init.h"
# include "input.h"
# include "minishell.h"

int		valid_env_start(char c);
int		valid_var_char(char c);
int		find_quote_end(char *s, int start, char quote_char);
int		find_var_end(char *str, int start);
char	*set_unquoted_vars(t_app *app, int *pos, int *last_pos, int start);
char	*process_unquoted_text(char *arg, int start, int end, t_app *app);
char	*handle_unquoted_part(char *arg, int start, int *i, t_app *app);
char	*add_text_before_dollar(char *result, char *arg, int last_pos, int pos,
			t_app *app);
char	*handle_remaining_text(char *result, char *arg, int last_pos, int end,
			t_app *app);
char	*process_argument(char *arg, t_app *app);
void	traverse_cmd(t_cmd *cmd_head, t_app *app);
int		handle_expansion(t_app *app);
char	*process_variable_expansion(char *section, t_app *app);
char	*process_section_literal(char *s, int start, int end, t_app *app);
char	*process_section_expand(char *s, int start, int end, t_app *app);
char	*handle_quoted_part(char *arg, int *i, t_app *app);
void	set_mixed_quotes_vars(t_app *app, char **res, int *i);
char	*process_mixed_quotes(char *arg, t_app *app);
int		contains_quotes(char *s);
char	*look_up_env(char *var_name, t_env *env);
char	*get_var_value(char *str, int start, int end, t_app *app);
char	*handle_dollar_quote(char *str, int *pos, t_app *app);
char	*handle_dollar_single_quote(char *str, int *pos, t_app *app);
char	*handle_regular_var(char *str, int *pos, t_app *app);
void	set_build_vars_variables(int *pos, int *last_pos, char **res,
			t_app *app);
char	*add_text_part(char *str, int start, int end, t_app *app);
char	*join_parts(char *result, char *part, t_app *app);
char	*handle_dollar_patterns(char *str, int *pos, t_app *app);
char	*build_vars(char *str, t_app *app);

#endif
