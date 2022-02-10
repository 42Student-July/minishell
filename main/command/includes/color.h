/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:56:00 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/09 17:57:16 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

/* Foreground color */
# define F_RED			"\x1b[31m"
# define F_GREEN		"\x1b[32m"
# define F_YELLOW		"\x1b[33m"
# define F_BLUE			"\x1b[34m"
# define F_PINK			"\x1b[35m"
# define F_LIGHT_BLUE	"\x1b[36m"
# define F_WHITE		"\x1b[37m"
# define F_RESET		"\x1b[39m"

/* Background color */
# define B_RED			"\x1b[41m"
# define B_GREEN		"\x1b[42m"
# define B_YELLOW		"\x1b[43m"
# define B_BLUE			"\x1b[44m"
# define B_PINK			"\x1b[45m"
# define B_LIGHT_BLUE	"\x1b[46m"
# define B_GRAY			"\x1b[47m"
# define B_RESET		"\x1b[49m"

/* Other decorations */
# define UNDERLINE		"\x1b[4m"
# define BOLD			"\x1b[1m"
# define O_RESET		"\x1b[0m"

#endif
