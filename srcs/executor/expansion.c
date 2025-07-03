#include "minishell.h"

int	valid_env_start(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| c == '_'
		|| c == '?');
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

char	*add_text_part(char *str, int start, int end, t_app *app)
{
	char	*temp;

	if (start >= end)
		return ("");
	temp = ft_strndup(str + start, end - start, &app->curr_gc);
	if(!temp)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (temp);
}

char	*get_var_value(char *str, int start, int end, t_app *app)
{
	char	*var_name;
	char	*value;

	var_name = ft_strndup(str + start, end - start, &app->curr_gc);
	if(!var_name)
		cleanup_and_exit(app, EXIT_FAILURE);
	value = look_up_env(var_name, app->env_head);
	return (value);
}

int	find_var_end(char *str, int start)
{
	int	i;

	i = start;
	if (str[i] == '?')
		return (i + 1);
	while (str[i] && valid_var_char(str[i]))
		i++;
	return (i);
}

char	*join_parts(char *result, char *part, t_app *app)
{
	char	*new_result;

	new_result = ft_strjoin(result, part, &app->curr_gc);
	if(!new_result)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (new_result);
}

char	*handle_dollar_quote(char *str, int *pos, t_app *app)
{
	char	*part;
	int		last_pos;

	(*pos)++;
	(*pos)++;
	last_pos = *pos;
	while (str[*pos] && str[*pos] != '"')
		(*pos)++;
	part = ft_strndup(str + last_pos, *pos - last_pos, &app->curr_gc);
	if(!part)
		cleanup_and_exit(app, EXIT_FAILURE);
	part = process_variable_expansion(part, app);
	if (str[*pos] == '"')
		(*pos)++;
	return (part);
}

char	*handle_dollar_single_quote(char *str, int *pos, t_app *app)
{
	char	*part;
	int		last_pos;

	(*pos)++;
	(*pos)++;
	last_pos = *pos;
	while (str[*pos] && str[*pos] != '\'')
		(*pos)++;
	part = ft_strndup(str + last_pos, *pos - last_pos, &app->curr_gc);
	if(!part)
		cleanup_and_exit(app, EXIT_FAILURE);
	if (str[*pos] == '\'')
		(*pos)++;
	return (part);
}

char	*handle_regular_var(char *str, int *pos, t_app *app)
{
	char	*part;
	int		last_pos;

	last_pos = ++(*pos);
	*pos = find_var_end(str, *pos);
	part = get_var_value(str, last_pos, *pos, app);
	return (part);
}

void	set_build_vars_variables(int *pos, int *last_pos, char **res, t_app *app)
{
	*pos = 0;
	*last_pos = 0;
	*res = ft_strdup("", &app->curr_gc);
	if(!*res)
		cleanup_and_exit(app, EXIT_FAILURE);
}

char	*handle_dollar_patterns(char *str, int *pos, t_app *app)
{
	if (str[*pos + 1] == '"')
		return (handle_dollar_quote(str, pos, app));
	else if (str[*pos + 1] == '\'')
		return (handle_dollar_single_quote(str, pos, app));
	else
		return (handle_regular_var(str, pos, app));
}

char	*build_vars(char *str, t_app *app)
{
	char	*result;
	char	*part;
	int		pos;
	int		last_pos;

	set_build_vars_variables(&pos, &last_pos, &result, app);
	while (str[pos])
	{
		if (str[pos] == '$' && str[pos + 1] && (valid_env_start(str[pos + 1]) 
			|| str[pos + 1] == '"' || str[pos + 1] == '\''))
		{
			part = add_text_part(str, last_pos, pos, app);
			result = join_parts(result, part, app);
			part = handle_dollar_patterns(str, &pos, app);
			result = join_parts(result, part, app);
			last_pos = pos;
		}
		else
			pos++;
	}
	part = add_text_part(str, last_pos, pos, app);
	return (join_parts(result, part, app));
}

char	*process_variable_expansion(char *section, t_app *app)
{
	return (build_vars(section, app));
}

char	*process_section_literal(char *s, int start, int end, t_app *app)
{
	char	*res;

	res = ft_strndup(s + start, end - start, &app->curr_gc);
	if(!res)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (res);
}

char	*process_section_expand(char *s, int start, int end, t_app *app)
{
	char	*section;

	section = ft_strndup(s + start, end - start, &app->curr_gc);
	if(!section)
		cleanup_and_exit(app, EXIT_FAILURE);
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

char	*add_text_before_dollar(char *result, char *arg, int last_pos, int pos, t_app *app)
{
	char	*part;

	if (pos > last_pos)
	{
		part = ft_strndup(arg + last_pos, pos - last_pos, &app->curr_gc);
		if(!part)
			cleanup_and_exit(app, EXIT_FAILURE);
		part = process_variable_expansion(part, app);
		result = ft_strjoin(result, part, &app->curr_gc);
		if(!result)
			cleanup_and_exit(app, EXIT_FAILURE);
	}
	return (result);
}

char	*handle_remaining_text(char *result, char *arg, int last_pos, int end, t_app *app)
{
	char	*part;

	if (end > last_pos)
	{
		part = ft_strndup(arg + last_pos, end - last_pos, &app->curr_gc);
		if(!part)
			cleanup_and_exit(app, EXIT_FAILURE);
		part = process_variable_expansion(part, app);
		result = ft_strjoin(result, part, &app->curr_gc);
		if(!result)
			cleanup_and_exit(app, EXIT_FAILURE);
	}
	return (result);
}
char	*set_unquoted_vars(t_app *app, int *pos, int *last_pos, int start)
{
	char	*result;
	result = ft_strdup("", &app->curr_gc);
	if(!result)
		cleanup_and_exit(app, EXIT_FAILURE);
	*pos = start;
	*last_pos = start;
	return (result);

}
char	*process_unquoted_text(char *arg, int start, int end, t_app *app)
{
	char	*result;
	char	*part;
	int		pos;
	int		last_pos;

	result = set_unquoted_vars(app, &pos, &last_pos, start);
	while (pos < end)
	{
		if (arg[pos] == '$' && pos + 1 < end && (arg[pos + 1] == '"' 
			|| arg[pos + 1] == '\''))
		{
			result = add_text_before_dollar(result, arg, last_pos, pos, app);
			part = handle_dollar_patterns(arg, &pos, app);
			result = ft_strjoin(result, part, &app->curr_gc);
			if (!result)
				cleanup_and_exit(app, EXIT_FAILURE);
			last_pos = pos;
		}
		else
			pos++;
	}
	return (handle_remaining_text(result, arg, last_pos, end, app));
}

char	*handle_unquoted_part(char *arg, int start, int *i, t_app *app)
{
	int	end;

	end = start;
	while (arg[end] && arg[end] != '"' && arg[end] != '\'')
	{
		if (arg[end] == '$' && (arg[end + 1] == '"' || arg[end + 1] == '\''))
		{
			end += 2;
			if (arg[end - 1] == '"')
			{
				while (arg[end] && arg[end] != '"')
					end++;
			}
			else
			{
				while (arg[end] && arg[end] != '\'')
					end++;
			}
			if (arg[end])
				end++;
		}
		else
			end++;
	}
	return (*i = end, process_unquoted_text(arg, start, end, app));
}

void	set_mixed_quotes_vars(t_app *app, char **res, int *i)
{
	*i = 0;
	*res = ft_strdup("", &app->curr_gc);
	if(!*res)
		cleanup_and_exit(app, EXIT_FAILURE);
}

char	*process_mixed_quotes(char *arg, t_app *app)
{
	char	*result;
	char	*part;
	int		i;
	int		start;

	set_mixed_quotes_vars(app, &result, &i);
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
		if(!result)
			cleanup_and_exit(app, EXIT_FAILURE);
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