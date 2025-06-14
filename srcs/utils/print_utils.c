#include "minishell.h"

char	*token_to_str(t_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return ("WORD");
	case TOKEN_OR:
		return ("OR");
	case TOKEN_AND:
		return ("AND");
	case TOKEN_PIPE:
		return ("PIPE");
	case TOKEN_REDIR_IN:
		return ("REDIR_IN");
	case TOKEN_REDIR_OUT:
		return ("REDIR_OUT");
	case TOKEN_REDIR_APPEND:
		return ("REDIR_APPEND");
	case TOKEN_REDIR_HEREDOC:
		return ("REDIR_APPEND");
	case TOKEN_OPEN_PARENTHESE:
		return ("OPEN_PARENTHESE");
	case TOKEN_CLOSE_PARENTHESE:
		return ("CLOSE_PARENTHESE");
	case TOKEN_IO_NUMBER:
		return ("IO_NUMBER");
	case TOKEN_NEW_LINE:
		return ("NEW_LINE");
	case TOKEN_EOF:
		return ("EOF");
	default:
		return ("UNKNOWN TOKEN");
	}
}

void	display_tokens(t_token *head, char *input)
{
	int		i;
	t_token	*lst;

	i = 0;
	lst = head;
	printf("initial command -> %s\n", input);
	while (lst)
	{
		printf("lst->type = %s ", token_to_str(lst->type));
		if (!lst->value)
			printf("VALUE: NULL");
		else
			printf("VALUE : %s", lst->value);
		printf("\n");
		lst = lst->next;
	}
}
