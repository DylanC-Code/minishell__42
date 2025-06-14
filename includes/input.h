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
