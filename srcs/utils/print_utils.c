#include "minishell.h"

char	*token_to_str(t_token_type type)
{
	switch (type)
	{
	case WORD:
		return ("WORD");
	case OR:
		return ("OR");
	case AND:
		return ("AND");
	case PIPE:
		return ("PIPE");
	case REDIR_IN:
		return ("REDIR_IN");
	case REDIR_OUT:
		return ("REDIR_OUT");
	case REDIR_APPEND:
		return ("REDIR_APPEND");
	case REDIR_HEREDOC:
		return ("REDIR_APPEND");
	case OPEN_PARENTHESE:
		return ("OPEN_PARENTHESE");
	case CLOSE_PARENTHESE:
		return ("CLOSE_PARENTHESE");
	case IO_NUMBER:
		return ("IO_NUMBER");
	case NEW_LINE:
		return ("NEW_LINE");
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
