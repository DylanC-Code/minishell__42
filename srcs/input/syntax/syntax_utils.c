/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:31:37 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 13:14:44 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_word(char *word)
{
	size_t	len;
	char	quote_type;

	len = ft_strlen(word);
	if (!ft_ischarset(*word, "'\""))
		return (true);
	quote_type = *word;
	if (len == 1)
		return (print_unexpected_eof(quote_type));
	if (word[len - 1] != quote_type)
		return (print_unexpected_eof(quote_type));
	return (true);
}
