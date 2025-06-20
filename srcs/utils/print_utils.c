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
		return ("REDIR_HEREDOC");
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
	t_cmd			*current_cmd;
	t_redir_list *curr_list;
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
			curr_list = current_cmd->redir_list;
			printf("  Command %d: \n", cmd_num);
			if (current_cmd->args)
			{
				i = 0;
				for(int i = 0; curr_list; curr_list = curr_list->next, i++)
					printf("[Node %d] name->%s type->%s\n", i, curr_list->name, token_to_str(curr_list->type));
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

#include <stdio.h>
#include "colors.h"
#include <stdio.h>
#include <unistd.h> // pour usleep
#include "colors.h"

static void	print_line_slow(const char *line, useconds_t delay)
{
	while (*line)
	{
		write(STDOUT_FILENO, line, 1);
		usleep(delay); // e.g. 5000 = 5ms
		line++;
	}
}

void	print_banner(void)
{
	const char *banner[] = {
		SHELL_EMOJI " Welcome to\n\n",
		BBLUE " ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n",
		" ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n",
		" ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n",
		" ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n",
		" ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n",
		" ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n" RESET,
		"\n",
		BGREEN "     🧠 Ctrl-C: interrupt | Ctrl-D: exit | Ctrl-\\: ignored\n" RESET,
		BYELLOW "     📁 PWD: shown in prompt | 💡 Builtins: cd, echo, pwd...\n" RESET,
		BMAGENTA "     🔧 Redirections | 🔗 Pipes | 🌱 Environment | ❓ $?, $VAR\n\n" RESET,
		NULL
	};

	for (int i = 0; banner[i]; i++)
		print_line_slow(banner[i], 500); // 500µs par caractère (modifiable)
}
