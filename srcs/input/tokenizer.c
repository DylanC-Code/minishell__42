/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/13 14:23:44 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_token_back(t_token **token_list, t_token *new_token);
t_token			*get_token(t_app *app, char *str);
char			*get_word(char *str);
char			*get_value_between(char *str, char quote_delimiter);
char			*get_operator(char *str);
static void		add_token_back(t_token **token_list, t_token *new_token);
t_token_type	get_token_type(char *token_value);

t_token	*tokenizer(t_app *app, char *line)
{
	t_token	*head_token;
	t_token	*new_token;
	size_t	i;

	i = -1;
	head_token = NULL;
	while (line && line[++i])
	{
		if (ft_isspace(line[i]))
			continue ;
		new_token = get_token(app, line + i);
		// if (!new_token)
		// 	return ; // TODO: handle error
		add_token_back(&head_token, new_token);
		i += ft_strlen(new_token->value) - 1;
	}
	return (head_token);
}

typedef enum e_token_state
{
	DEFAULT,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
}				t_token_state;

#define OPERATORS "<>|&()"

t_token	*get_token(t_app *app, char *str)
{
	t_token	*new_token;

	new_token = gc_malloc(sizeof(t_token), &app->garb_head);
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

char	*get_word(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (ft_ischarset(str[i], OPERATORS) || ft_isspace(str[i]))
			break ;
	return (ft_strndup(str, i));
}

char	*get_value_between(char *str, char quote_delimiter)
{
	size_t	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] != quote_delimiter)
			continue ;
		if (str[i - 1] != '\\')
			break ;
	}
	return (ft_strndup(str, i + 1));
}

char	*get_operator(char *str)
{
	if (str[0] != str[1])
		return (ft_strndup(str, 1));
	return (ft_strndup(str, 2));
}

static void	add_token_back(t_token **token_list, t_token *new_token)
{
	t_token	*next;

	if (!*token_list)
	{
		*token_list = new_token;
		return ;
	}
	next = *token_list;
	while (next->next)
		next = next->next;
	next->next = new_token;
}
