/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 10:56:15 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

t_token	*tokenizer(char *line, t_garbage **gb_list);

/* =============== Definition ================ */

t_token	*tokenizer(char *line, t_garbage **gb_list)
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
		new_token = get_token(&line[i], gb_list);
		if (!new_token)
			return (NULL);
		add_token_back(&head_token, new_token);
		i += ft_strlen(new_token->value) - 1;
	}
	append_newline_token(&head_token, gb_list);
	return (head_token);
}
