/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:34:32 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 10:40:47 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

#include <stdlib.h>
# include "memory.h"

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

typedef struct s_redir_list
{
	char				*name;
	t_token_type		type;
	struct s_redir_list	*next;
}						t_redir_list;
typedef struct s_cmd
{
	char			**args;			// arguments
	char			*input_file;	// < 
	char			*output_file;	// > 
	int				append_output;	// 1 = >>, 0 = >
	char			*heredoc_delim;	// << (heredoc)
	t_redir_list	*redir_list;
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

typedef struct s_parser
{
	t_cmd_sequence	*seq_head;
	t_cmd_sequence	*curr_seq;
	t_cmd			*cmd_head;
	size_t			arg_count;
	t_token			*token;
	t_redir_list	*redir_head;
}					t_parser;

t_cmd *cmd_builder(t_token *token);
t_cmd_sequence *sequence_builder(void);
t_cmd_sequence *parse_tokens(t_token *head);
void display_seq(t_cmd_sequence *seq_head);
int	handle_redirection(t_parser *parser);
int	handle_logical_op(t_parser *parser);
int	handle_pipe(t_parser *parser);
t_redir_list	*redir_node_builder(char *name, t_token_type type);
void	redir_node_addback(t_redir_list **redir_list, char *name, t_token_type type);
int is_redirection_operator(t_token_type type);
void	display_redir_list(t_redir_list *head);
char	*token_to_str(t_token_type type);

/* ************************* */
/* ******* Tokenizer ******* */
/* ************************* */

t_token				*get_token(char *str, t_garbage **gb_list);
t_token_type		get_token_type(char *token_value);

char				*get_word(char *str);
char				*get_value_between(char *str, char quote_delimiter);
char				*get_operator(char *str);

void				add_token_back(t_token **token_list, t_token *new_token);

t_token				*tokenizer(char *line, t_garbage **gb_list);

#endif
