/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:50:25 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 16:50:28 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/* === ANSI RESET === */
# define RESET "\033[0m"

/* === TEXT STYLES === */
# define BOLD "\033[1m"
# define DIM "\033[2m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define BLINK "\033[5m"
# define REVERSE "\033[7m"

/* === STANDARD COLORS === */
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

/* === BOLD COLORS === */
# define BBLACK "\033[1;30m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define BMAGENTA "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BWHITE "\033[1;37m"

/* === BACKGROUND COLORS === */
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"

/* === HIGH INTENSITY COLORS === */
# define HRED "\033[0;91m"
# define HGREEN "\033[0;92m"
# define HYELLOW "\033[0;93m"
# define HBLUE "\033[0;94m"
# define HMAGENTA "\033[0;95m"
# define HCYAN "\033[0;96m"
# define HWHITE "\033[0;97m"

/* === EMOJIS === */
# define SHELL_EMOJI "🐚"
# define CHECK_EMOJI "✅"
# define CROSS_EMOJI "❌"
# define ARROW_EMOJI "➡️ "
# define ERROR_EMOJI "⚠️ "
# define INFO_EMOJI "ℹ️ "

/* === PROMPT HELPERS FOR READLINE (non-counted chars) === */
# define BEGIN_IGNORE "\001"
# define END_IGNORE "\002"

/* === PROMPT BUILDER EXAMPLE === */
# define PROMPT BEGIN_IGNORE BBLUE END_IGNORE SHELL_EMOJI " " BEGIN_IGNORE BBLUE END_IGNORE "minishell" BEGIN_IGNORE RESET END_IGNORE ":" BEGIN_IGNORE BLUE END_IGNORE "%s" BEGIN_IGNORE RESET END_IGNORE "$ "

#endif
