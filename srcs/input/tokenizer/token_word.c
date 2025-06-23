/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:25:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 21:53:10 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void	handle_word_token(t_token *token, char *str, t_garbage **gc);
void	handle_single_quote_token(t_token *token, char *str, t_garbage **gc);
void	handle_double_quote_token(t_token *token, char *str, t_garbage **gc);

/* =============== Definition ================ */

void	handle_word_token(t_token *token, char *str, t_garbage **gc)
{
	char	symbols[] = "<>|&()'\"";
	size_t	i;

	i = -1;
	token->type = TOKEN_WORD;
	while (str[++i])
		if (ft_ischarset(str[i], symbols) || ft_isspace(str[i]))
			break ;
	token->value = ft_strndup(str, i, gc);
}

void	handle_single_quote_token(t_token *token, char *str, t_garbage **gc)
{
	size_t	i;

	i = 0;
	token->type = TOKEN_WORD;
	while (str[++i])
	{
		if (str[i] != '\'')
			continue ;
		i++;
		break ;
	}
	token->value = ft_strndup(str, i, gc);
}

void	handle_double_quote_token(t_token *token, char *str, t_garbage **gc)
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
	token->value = ft_strndup(str, i + 1, gc);
}
