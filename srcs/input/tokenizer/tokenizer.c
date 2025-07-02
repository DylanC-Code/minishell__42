/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 15:50:07 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Definition ================ */

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
		new_token = get_token(&line[i], &app->curr_gc);
		if (!new_token)
			return (NULL);
		add_token_back(&head_token, new_token);
		i += ft_strlen(new_token->value) - 1;
	}
	append_newline_token(&head_token, &app->curr_gc);
	return (head_token);
}
