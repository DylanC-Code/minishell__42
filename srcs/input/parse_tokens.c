/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saal-kur <saal-kur@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-13 14:11:20 by saal-kur          #+#    #+#             */
/*   Updated: 2025-06-13 14:11:20 by saal-kur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_sequence *parse_tokens(t_token *head)
{
	t_cmd_sequence *seq_head;
	t_cmd_sequence *curr_seq;
	t_cmd *cmd_head;

	seq_head = sequence_builder();
	cmd_head = cmd_builder();
	curr_seq = seq_head;


}