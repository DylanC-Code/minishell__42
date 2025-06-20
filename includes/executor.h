/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:56 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 16:26:24 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "input.h"
# include "minishell.h"

void	handle_exec(t_app *app, t_cmd_sequence *head_seq,
			t_redir_list *redir_head);

#endif
