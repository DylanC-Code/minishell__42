/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/10 15:59:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	char			*res;
	char			*prompt;
	DIR				*di;
	struct dirent	*dir;

	di = opendir("test");
	dir = readdir(di);
    // printf("%d\n", )
	return (0);
}
