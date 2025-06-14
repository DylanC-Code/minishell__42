/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:25:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 12:09:04 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void	handle_word_token(t_token *token, char *str);
void	handle_single_quote_token(t_token *token, char *str);
void	handle_double_quote_token(t_token *token, char *str);

/* =============== Definition ================ */

void	handle_word_token(t_token *token, char *str)
{
	size_t	i;

	i = -1;
	token->type = TOKEN_WORD;
	while (str[++i])
		if (ft_ischarset(str[i], OPERATORS) || ft_isspace(str[i]))
			break ;
	token->value = ft_strndup(str, i);
}

void	handle_single_quote_token(t_token *token, char *str)
{
	size_t	i;

	i = 0;
	token->type = TOKEN_WORD;
	while (str[++i])
	{
		if (str[i] != '\'')
			continue ;
		if (str[i - 1] != '\\')
			break ;
	}
	token->value = ft_strndup(str, i + 1);
}

void	handle_double_quote_token(t_token *token, char *str)
{
	size_t	i;

	i = 0;
	token->type = TOKEN_WORD;
	while (str[++i])
	{
		if (str[i] != '\"')
			continue ;
		if (str[i - 1] != '\\')
			break ;
	}
	token->value = ft_strndup(str, i + 1);
}
