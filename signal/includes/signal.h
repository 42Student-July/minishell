/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:34:51 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/12 01:47:22 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

// set_signal.c

void	set_interactive_sigint(void);
void	set_dfl_sigint(void);
void	set_dfl_sigquit(void);

#endif