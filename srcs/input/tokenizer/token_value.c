/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:25:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 10:29:38 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

char	*get_word(char *str);
char	*get_value_between(char *str, char quote_delimiter);
char	*get_operator(char *str);

/* =============== Definition ================ */

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
