/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:06:43 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/07 11:06:44 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/* === ANSI RESET === */
# define RESET "\001\033[0m\002"

/* === TEXT STYLES === */
# define BOLD "\001\033[1m\002"
# define DIM "\001\033[2m\002"
# define ITALIC "\001\033[3m\002"
# define UNDERLINE "\001\033[4m\002"
# define BLINK "\001\033[5m\002"
# define REVERSE "\001\033[7m\002"

/* === STANDARD COLORS === */
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"

/* === BOLD COLORS === */
# define BBLACK "\001\033[1;30m\002"
# define BRED "\001\033[1;31m\002"
# define BGREEN "\001\033[1;32m\002"
# define BYELLOW "\001\033[1;33m\002"
# define BBLUE "\001\033[1;34m\002"
# define BMAGENTA "\001\033[1;35m\002"
# define BCYAN "\001\033[1;36m\002"
# define BWHITE "\001\033[1;37m\002"

/* === BACKGROUND COLORS === */
# define BG_BLACK "\001\033[40m\002"
# define BG_RED "\001\033[41m\002"
# define BG_GREEN "\001\033[42m\002"
# define BG_YELLOW "\001\033[43m\002"
# define BG_BLUE "\001\033[44m\002"
# define BG_MAGENTA "\001\033[45m\002"
# define BG_CYAN "\001\033[46m\002"
# define BG_WHITE "\001\033[47m\002"

/* === HIGH INTENSITY COLORS === */
# define HRED "\001\033[0;91m\002"
# define HGREEN "\001\033[0;92m\002"
# define HYELLOW "\001\033[0;93m\002"
# define HBLUE "\001\033[0;94m\002"
# define HMAGENTA "\001\033[0;95m\002"
# define HCYAN "\001\033[0;96m\002"
# define HWHITE "\001\033[0;97m\002"

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

#endif
