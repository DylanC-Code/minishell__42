/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:45:36 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/25 10:11:23 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_env_start(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| c == '_');
}

int	valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}

char	*look_up_env(char *var_name, t_env *env)
{
	t_env	*curr_env;

	curr_env = env;
	while (curr_env)
	{
		if (ft_strcmp(curr_env->key, var_name) == 0)
			return (curr_env->value);
		curr_env = curr_env->next;
	}
	return ("");
}

int	find_quote_end(char *s, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (s[i] && s[i] != quote_char)
		i++;
	return (i);
}

char	*build_var(char *s, int *i, t_app *app)
{
	char	*result;
	char	*var_name;
	char	*value;
	int		var_start;

	result = ft_strndup(s, *i, &app->curr_gc);
	var_start = *i + 1;
	(*i)++;
	while (s[*i] && valid_var_char(s[*i]))
		(*i)++;
	var_name = ft_strndup(s + var_start, *i - var_start, &app->curr_gc);
	value = look_up_env(var_name, app->env_head);
	result = ft_strjoin(result, value, &app->curr_gc);
	return (ft_strjoin(result, s + *i, &app->curr_gc));
}

char	*process_variable_expansion(char *section, t_app *app)
{
	int	i;

	i = 0;
	while (section[i])
	{
		if (section[i] == '$' && valid_env_start(section[i + 1]))
			return (build_var(section, &i, app));
		i++;
	}
	return (ft_strdup(section, &app->curr_gc));
}

char	*process_section_literal(char *s, int start, int end, t_app *app)
{
	return (ft_strndup(s + start, end - start, &app->curr_gc));
}

char	*process_section_expand(char *s, int start, int end, t_app *app)
{
	char	*section;

	section = ft_strndup(s + start, end - start, &app->curr_gc);
	return (process_variable_expansion(section, app));
}

char	*handle_quoted_part(char *arg, int *i, t_app *app)
{
	char	quote_char;
	int		end;

	quote_char = arg[*i];
	end = find_quote_end(arg, *i, quote_char);
	if (quote_char == '"')
		return (process_section_expand(arg, *i + 1, end, app));
	return (process_section_literal(arg, *i + 1, end, app));
}

char	*handle_unquoted_part(char *arg, int start, int *i, t_app *app)
{
	while (arg[*i] && arg[*i] != '"' && arg[*i] != '\'')
		(*i)++;
	return (process_section_expand(arg, start, *i, app));
}

char	*process_mixed_quotes(char *arg, t_app *app)
{
	char	*result;
	char	*part;
	int		i;
	int		start;

	result = ft_strdup("", &app->curr_gc);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			part = handle_quoted_part(arg, &i, app);
			i = find_quote_end(arg, i, arg[i]) + 1;
		}
		else
		{
			start = i;
			part = handle_unquoted_part(arg, start, &i, app);
		}
		result = ft_strjoin(result, part, &app->curr_gc);
	}
	return (result);
}

int	contains_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*process_argument(char *arg, t_app *app)
{
	if (contains_quotes(arg))
		return (process_mixed_quotes(arg, app));
	return (process_variable_expansion(arg, app));
}

void	traverse_cmd(t_cmd *cmd_head, t_app *app)
{
	t_cmd	*curr;
	int		i;

	curr = cmd_head;
	while (curr)
	{
		i = 0;
		while (curr->args[i])
		{
			curr->args[i] = process_argument(curr->args[i], app);
			i++;
		}
		curr = curr->next;
	}
}

int	handle_expansion(t_app *app, t_cmd_sequence *head_seq)
{
	t_cmd_sequence	*curr_seq;

	curr_seq = head_seq;
	if (!app || !head_seq)
		return (0);
	while (curr_seq)
	{
		traverse_cmd(curr_seq->cmds, app);
		curr_seq = curr_seq->next;
	}
	return (1);
}
