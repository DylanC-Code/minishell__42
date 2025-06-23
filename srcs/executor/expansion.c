/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:45:36 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/23 11:39:41 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_env_start(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}

char	*is_env_var(char *s)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && valid_env_start(s[i + 1]))
		{
			i++;
			start = i;
			while (s[i] && valid_var_char(s[i]))
				i++;
			return (ft_strndup(s + start, i - start));
		}
		i++;
	}
	return (NULL);
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

char	*resolved_env(char *cmd, char *var_name, char *env_value)
{
	char	*res;
	int		i;
	int		var_len;

	i = 0;
	res = NULL;
	var_len = ft_strlen(var_name);
	while (cmd[i] && cmd[i] != '$')
		i++;
	if (i > 0)
		res = ft_strndup(cmd, i);
	else
		res = ft_strdup("");
	res = ft_strjoin(res, env_value);
	res = ft_strjoin(res, cmd + i + 1 + var_len);
	return (res);
}

void	traverse_cmd(t_cmd *cmd_head, t_app *app)
{
	t_cmd	*curr;
	char	*value;
	char	*var_name;
	int		i;

	curr = cmd_head;
	while (curr)
	{
		i = 0;
		while (curr->args[i])
		{
			var_name = is_env_var(curr->args[i]);
			if (var_name)
			{
				value = look_up_env(var_name, app->env_head);
				printf("VAR_NAME->%s VALUE->%s\n", var_name, value);
				printf("RESOLVED_ENV->%s\n", resolved_env(curr->args[i],
						var_name, value));
				curr->args[i] = resolved_env(curr->args[i], var_name, value);
			}
			i++;
		}
		curr = curr->next;
	}
}

int	handle_expansion(t_app *app, t_cmd_sequence *head_seq)
{
	t_cmd_sequence *curr_seq;

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
