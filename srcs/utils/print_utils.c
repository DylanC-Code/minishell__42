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
	case TOKEN_OPEN_PARENTHESIS:
		return ("OPEN_PARENTHESE");
	case TOKEN_CLOSE_PARENTHESIS:
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
	t_token	*lst;

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


void	display_seq(t_cmd_sequence *seq_head)
{
	t_cmd_sequence	*current_seq;
	t_cmd		*current_cmd;
	int		seq_num;
	int		cmd_num;
	int		i;

	current_seq = seq_head;
	seq_num = 1;
	while (current_seq)
	{
		printf("SEQUENCE %d:\n", seq_num);
		current_cmd = current_seq->cmds;
		cmd_num = 1;
		while (current_cmd)
		{
			printf("  Command %d: ", cmd_num);
			if (current_cmd->args)
			{
				i = 0;
				while (current_cmd->args[i])
				{
					printf("[%d]%s ", i, current_cmd->args[i]);
					i++;
				}
			}
			printf("\n");
			if (current_cmd->input_file)
				printf("    Input: %s\n", current_cmd->input_file);
			if (current_cmd->output_file)
			{
				if (current_cmd->append_output == 1)
					printf("    Output (append): %s\n", current_cmd->output_file);
				else
					printf("    Output: %s\n", current_cmd->output_file);
			}
			if (current_cmd->heredoc_delim)
				printf("    Heredoc: %s\n", current_cmd->heredoc_delim);
			if (current_cmd->next)
				printf("    |\n");
			current_cmd = current_cmd->next;
			cmd_num++;
		}
		if (current_seq->logical_op == LOGICAL_AND)
			printf("  &&\n");
		else if (current_seq->logical_op == LOGICAL_OR)
			printf("  ||\n");
		printf("\n");
		current_seq = current_seq->next;
		seq_num++;
	}
}