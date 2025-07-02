/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:31:37 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 15:46:22 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_quote(char *word, size_t *i, char quote_char);

bool	check_word(t_app *app, char *word)
{
	size_t	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '\'' && !check_quote(word, &i, '\''))
			return (unexpected_eof_error(app, "'"), false);
		else if (word[i] == '"' && !check_quote(word, &i, '"'))
			return (unexpected_eof_error(app, "\""), false);
	}
	return (true);
}

static bool	check_quote(char *word, size_t *i, char quote_char)
{
	(*i)++;
	while (word[*i] && word[*i] != quote_char)
		(*i)++;
	return (word[*i] == quote_char);
}
