/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:34:32 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 15:23:53 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>

# define APPEND_END_FILE 1
# define APPEND_BEGIN_FILE 0
# define LOGICAL_OR 1
# define LOGICAL_AND 2

typedef enum e_token_type
{
	TOKEN_WORD = 1,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_OPEN_PARENTHESIS,
	TOKEN_CLOSE_PARENTHESIS,
	TOKEN_IO_NUMBER,
	TOKEN_NEW_LINE,
	TOKEN_EOF,
}							t_token_type;

typedef enum e_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}							t_quote;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
}							t_token;

typedef struct s_redir_list
{
	char					*name;
	t_token_type			type;
	int						fd;
	struct s_redir_list		*next;
}							t_redir_list;
typedef struct s_cmd
{
	pid_t					pid;
	char					**args;
	int						**pipes;
	int						fd_in;
	int						fd_out;
	bool					failed;
	t_garbage				*gc;
	t_redir_list			*redir_list;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_cmd_sequence
{
	t_cmd					*cmds;
	int						logical_op;
	int						last_exit_status;
	struct s_cmd_sequence	*next;

}							t_cmd_sequence;

typedef struct s_parser
{
	t_cmd_sequence			*seq_head;
	t_cmd_sequence			*curr_seq;
	t_cmd					*cmd_head;
	size_t					arg_count;
	t_token					*token;
	t_redir_list			*redir_head;
}							t_parser;

t_token						*read_complete_command(t_app *app);
char						*get_prompt(t_app *app);

/* ********************** */
/* ******* Syntax ******* */
/* ********************** */

bool						check_syntax(t_app *app, t_token *head_token);
bool						check_word(char *value);

/* ~ Command ~ */
t_status					syntax_handle_command(t_token **token_list);

/* ~ And Or Command ~ */
t_status					syntax_handle_and_or_command(t_token **token_list);

/* ~ Pipeline ~ */
t_status					syntax_handle_pipeline(t_token **token_list);

/* ~ Redirection ~ */
t_status					syntax_handle_redirection(t_token **token_list);
void						consume_redirection_sequence(t_token **token_list);
bool						is_redirection_op(t_token *token);
bool						is_redirection_sequence(t_token *token);

/* ~ Simple Command ~ */
t_status					syntax_handle_simple_command(t_token **token_list);

/* ~ Subshell ~ */
t_status					syntax_handle_subshell(t_token **token_list);

/* ~ Error ~ */
void						syntax_error(t_token *token);

void						display_seq(t_cmd_sequence *seq_head);
int							handle_redirection(t_parser *parser,
								t_garbage **gc);
int							handle_logical_operator(t_parser *parser,
								t_garbage **gc);
int							handle_pipe(t_parser *parser, t_garbage **gc);
t_redir_list				*redir_node_builder(char *name, t_token_type type,
								t_garbage **gc);
void						redir_node_addback(t_redir_list **redir_list,
								char *name, t_token_type type, t_garbage **gc);
int							is_redirection_operator(t_token_type type);
void						display_redir_list(t_redir_list *head);
char						*token_to_str(t_token_type type);

/* ************************* */
/* ******* Tokenizer ******* */
/* ************************* */

t_token						*tokenizer(char *line, t_garbage **gb_list);

t_token						*get_token(char *str, t_garbage **gb_list);

void						handle_word_token(t_token *token, char *str,
								t_garbage **gc);
void						handle_single_quote_token(t_token *token, char *str,
								t_garbage **gc);
void						handle_double_quote_token(t_token *token, char *str,
								t_garbage **gc);
void						handle_operator_token(t_token *token, char *str,
								t_garbage **gc);
void						handle_new_line_token(t_token *token,
								t_garbage **gc);
void						handle_io_number_token(t_token *token, char *str,
								t_garbage **gc);
void						handle_eof_token(t_token *token, t_garbage **gc);

bool						ft_is_ionumber(char *str);
void						add_token_back(t_token **token_list,
								t_token *new_token);
t_token						*append_newline_token(t_token **token_list,
								t_garbage **gc_list);

/* ************************* */
/* ******* Validator ******* */
/* ************************* */

t_cmd_sequence				*parse_tokens(t_token *head, t_garbage **gc);
void						display_seq(t_cmd_sequence *seq_head);
t_cmd						*cmd_builder(t_token *token, t_garbage **gc);
t_cmd_sequence				*sequence_builder(t_garbage **gc);
t_token						*get_token(char *str, t_garbage **gb_list);
t_token_type				get_token_type(char *token_value);

char						*get_word(char *str);
char						*get_value_between(char *str, char quote_delimiter);
char						*get_operator(char *str);

void						add_token_back(t_token **token_list,
								t_token *new_token);

t_token						*tokenizer(char *line, t_garbage **gb_list);

#endif
