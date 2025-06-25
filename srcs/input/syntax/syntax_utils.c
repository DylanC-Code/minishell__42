/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:31:37 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/25 11:36:46 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_single_quote(char *word, size_t *i);
static bool	check_double_quote(char *word, size_t *i);

bool	check_word(char *word)
{
	size_t	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '\'' && !check_single_quote(word, &i))
			return (print_unexpected_eof('\''), false);
		else if (word[i] == '"' && !check_double_quote(word, &i))
			return (print_unexpected_eof('"'), false);
	}
	return (true);
}

static bool	check_single_quote(char *word, size_t *i)
{
	(*i)++;
	while (word[*i] && word[*i] != '\'')
		(*i)++;
	if (word[*i] == '\'')
	{
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	check_double_quote(char *word, size_t *i)
{
	(*i)++;
	while (word[*i] && word[*i] != '"')
	{
		if (word[*i] == '\\' && word[*i + 1] == '"')
			(*i)++;
		(*i)++;
	}
	if (word[*i] == '"')
	{
		(*i)++;
		return (true);
	}
	return (false);
}
