/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:51:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/24 20:46:28 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define AND 7
# define OR 8

# define TRUE 1
# define FALSE 0

# define SINGLE_Q 0
# define DOUEBLE_Q 1

# define C_RESET "\033[0m"
# define C_YELLOW "\033[1;33m"
# define C_BLUE "\033[1;34m"
# define C_RED "\033[1;32m"
# define C_GREEN "\033[1;32m"
# define C_WHITE "\033[1;37m"

#endif
