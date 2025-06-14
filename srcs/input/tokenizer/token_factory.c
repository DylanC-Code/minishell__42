/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:23:42 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 10:29:12 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

t_token			*get_token(char *str, t_garbage **gb_list);
t_token_type	get_token_type(char *token_value);

/* =============== Definition ================ */

t_token	*get_token(char *str, t_garbage **gb_list)
{
	t_token	*new_token;

	new_token = gc_malloc(sizeof(t_token), gb_list);
	ft_bzero(new_token, sizeof(t_token));
	if (*str == '\'')
		new_token->value = get_value_between(str, '\'');
	else if (*str == '"')
		new_token->value = get_value_between(str, '"');
	else if (ft_ischarset(*str, OPERATORS))
		new_token->value = get_operator(str);
	else if (*str == '\n')
		new_token->value = ft_strdup("\n");
	else
		new_token->value = get_word(str);
	new_token->type = get_token_type(new_token->value);
	return (new_token);
}

t_token_type	get_token_type(char *token_value)
{
	if (*token_value == '\n')
		return (NEW_LINE);
	else if (ft_ischarset(*token_value, "'\""))
		return (WORD);
	else if (!ft_ischarset(*token_value, OPERATORS))
		return (WORD);
	if (ft_strlen(token_value) == 1)
	{
		if (*token_value == '|')
			return (PIPE);
		else if (*token_value == '<')
			return (REDIR_IN);
		else if (*token_value == '>')
			return (REDIR_OUT);
		else if (*token_value == '(')
			return (OPEN_PARENTHESE);
		else if (*token_value == ')')
			return (CLOSE_PARENTHESE);
	}
	if (*token_value == '|')
		return (OR);
	else if (*token_value == '<')
		return (REDIR_APPEND);
	else if (*token_value == '>')
		return (REDIR_HEREDOC);
	return (AND);
}
