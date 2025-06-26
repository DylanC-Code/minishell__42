/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:25:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 12:19:27 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void		handle_word_token(t_token *token, char *str, t_garbage **gc);
static void	handle_single_quote(char *str, size_t *i);
static void	handle_double_quote(char *str, size_t *i);

/* =============== Definition ================ */

void	handle_word_token(t_token *token, char *str, t_garbage **gc)
{
	char	symbols[] = "<>|&()";
	size_t	i;

	i = 0;
	token->type = TOKEN_WORD;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_single_quote(str, &i);
		else if (str[i] == '\"')
			handle_double_quote(str, &i);
		else if (ft_ischarset(str[i], symbols) || ft_isspace(str[i]))
			break ;
		else
			i++;
	}
	token->value = ft_strndup(str, i, gc);
}

static void	handle_single_quote(char *str, size_t *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
}

static void	handle_double_quote(char *str, size_t *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '\\' && str[*i + 1] == '\"')
			(*i)++;
		(*i)++;
	}
	if (str[*i] == '\"')
		(*i)++;
}
