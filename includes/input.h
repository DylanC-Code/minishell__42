/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:34:32 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 11:26:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include "memory.h"
# include <stdbool.h>

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
}					t_token_type;

typedef enum e_parse_status
{
	CMD_COMPLETE,
	CMD_INCOMPLETE,
	CMD_INVALID
}					t_parse_status;

typedef enum e_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}					t_quote;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

t_token				*read_complete_command(t_garbage **gc_current_cmd_line);

/* ********************** */
/* ******* Syntax ******* */
/* ********************** */

bool				check_syntax(t_token *head_token);

/* ~ Command ~ */
t_status			syntax_handle_command(t_token **token_list);

/* ~ And Or Command ~ */
t_status			syntax_handle_and_or_command(t_token **token_list);

/* ~ Pipeline ~ */
t_status			syntax_handle_pipeline(t_token **token_list);

/* ~ Redirection ~ */
t_status			syntax_handle_redirection(t_token **token_list);
void				consume_redirection_sequence(t_token **token_list);
bool				is_redirection_op(t_token *token);
bool				is_redirection_sequence(t_token *token);

/* ~ Simple Command ~ */
t_status			syntax_handle_simple_command(t_token **token_list);

/* ~ Subshell ~ */
t_status			syntax_handle_subshell(t_token **token_list);

/* ~ Error ~ */
void				syntax_error(t_token *token);

/* ************************* */
/* ******* Tokenizer ******* */
/* ************************* */

t_token				*tokenizer(char *line, t_garbage **gb_list);

t_token				*get_token(char *str, t_garbage **gb_list);

void				handle_word_token(t_token *token, char *str);
void				handle_single_quote_token(t_token *token, char *str);
void				handle_double_quote_token(t_token *token, char *str);
void				handle_operator_token(t_token *token, char *str);
void				handle_new_line_token(t_token *token);
void				handle_io_number_token(t_token *token, char *str);
void				handle_eof_token(t_token *token);

bool				ft_is_ionumber(char *str);
void				add_token_back(t_token **token_list, t_token *new_token);

/* ************************* */
/* ******* Validator ******* */
/* ************************* */

t_parse_status		check_command_status(char *line);

bool				quote_unclosed(t_token *token_head);

#endif
