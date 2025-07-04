/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:59:48 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:00:13 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
