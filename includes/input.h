/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:34:32 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 15:10:24 by dcastor          ###   ########.fr       */
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
	TOKEN_OPEN_PARENTHESE,
	TOKEN_CLOSE_PARENTHESE,
	TOKEN_IO_NUMBER,
	TOKEN_NEW_LINE,
	TOKEN_EOF,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/* ********************** */
/* ******* Syntax ******* */
/* ********************** */

bool				check_syntax(t_token *head_token);

/* ~ Command ~ */
t_status			syntax_handle_command(t_token **token_list);

/* ~ Pipeline ~ */
t_status			syntax_handle_pipeline(t_token **token_list);

/* ~ Redirection ~ */
t_status			syntax_handle_redirection(t_token **token_list);
void				consume_redirection_sequence(t_token **token_list);
bool				is_redirection_op(t_token *token);
bool				is_redirection_sequence(t_token *token);

/* ~ Subshell ~ */
t_status			syntax_handle_subshell(t_token **token_list);

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

#endif
