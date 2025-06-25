/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:31:37 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/25 15:41:41 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_quote(char *word, size_t *i, char quote_char);

bool	check_word(char *word)
{
	size_t	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '\'' && !check_quote(word, &i, '\''))
			return (print_unexpected_eof('\''), false);
		else if (word[i] == '"' && !check_quote(word, &i, '"'))
			return (print_unexpected_eof('"'), false);
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
