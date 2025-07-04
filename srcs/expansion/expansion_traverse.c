/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_traverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:45:36 by saal-kur          #+#    #+#             */
/*   Updated: 2025/07/04 11:36:49 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_argument(char *arg, t_app *app)
{
	if (contains_quotes(arg))
		return (process_mixed_quotes(arg, app));
	return (process_variable_expansion(arg, app));
}

void	traverse_cmd(t_cmd *cmd_head, t_app *app)
{
	t_cmd	*curr;
	int		i;

	curr = cmd_head;
	while (curr)
	{
		i = 0;
		while (curr->args[i])
		{
			curr->args[i] = process_argument(curr->args[i], app);
			i++;
		}
		curr = curr->next;
	}
}

int	handle_expansion(t_app *app)
{
	t_cmd_sequence	*curr_seq;

	if (!app || !app->seq_head)
		return (0);
	curr_seq = app->seq_head;
	while (curr_seq)
	{
		traverse_cmd(curr_seq->cmds, app);
		curr_seq = curr_seq->next;
	}
	return (1);
}
