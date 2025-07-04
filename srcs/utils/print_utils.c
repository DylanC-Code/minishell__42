/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:59:48 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:59:10 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h> // pour usleep

static void	print_line_slow(const char *line, useconds_t delay)
{
	while (*line)
	{
		write(STDOUT_FILENO, line, 1);
		usleep(delay);
		line++;
	}
}

void	print_banner(void)
{
	size_t		i;
	const char	*banner[] = {
		"🐚 Welcome to\n\n\033[1;34m",
		" ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n",
		" ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n",
		" ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n",
		" ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n",
		" ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n",
		" ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n",
		"\033[0m\n\033[1;32m",
		"     🧠 Ctrl-C: interrupt | Ctrl-D: exit | Ctrl-\\: ignored\n\033[0m",
		"\033[1;33m     📁 PWD: shown in prompt | 💡 Builtins: cd, echo, pwd...\n",
		"\033[0m\033[1;35m     🔧 Redirections | 🔗 Pipes | 🌱 Environment | ❓ $?,\
 $VAR\n\n\033[0m ", NULL};

	i = -1;
	while (banner[++i])
		print_line_slow(banner[i], 500);
}
