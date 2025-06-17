/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:34:32 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/13 14:10:59 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

#include <stdlib.h>

typedef enum e_token_type
{
	WORD,
	OR,
	AND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	OPEN_PARENTHESE,
	CLOSE_PARENTHESE,
	IO_NUMBER,
	NEW_LINE,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

#define APPEND_END_FILE 1
#define APPEND_BEGIN_FILE 0
#define LOGICAL_OR 1
#define LOGICAL_AND 2

typedef struct s_cmd
{
	char			**args;			// arguments
	char			*input_file;	// < 
	char			*output_file;	// > 
	int				append_output;	// 1 = >>, 0 = >
	char			*heredoc_delim;	// << (heredoc)
	struct s_cmd	*next;			// prochaine commande (si pipe il y a); NULL par défaut
}					t_cmd;

/*
	t_cmd represente une ou plusieurs commandes delimitées par un ou plusieurs pipes
	t_cmd_sequence represente tous les commandes séparés par un operateur logique
*/

typedef struct s_cmd_sequence
{
	t_cmd					*cmds; // commandes dans la séquence 
	int						logical_op; // operateur logique (facile de verifier la valeur de retour et savoir si on execute la prochaine sequence)
	struct	s_cmd_sequence	*next; // prochaine sequence de commandes 

} 					t_cmd_sequence;

t_cmd *cmd_builder(t_token *token);
t_cmd_sequence *sequence_builder(void);
t_cmd_sequence *parse_tokens(t_token *head);
void display_seq(t_cmd_sequence *seq_head);
int	handle_redirection(t_cmd **cmd, t_token **token);
int	handle_logical_op(t_cmd_sequence **curr_seq, t_cmd **cmd_head,t_token *token, size_t arg_count);
int	handle_pipe(t_cmd **cmd_head, t_token **token, size_t *arg_count);
#endif
