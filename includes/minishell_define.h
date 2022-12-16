/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:51:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 11:46:37 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define EMPTY 0
# define CMD 256
# define ARG 512
# define TRUNC 1
# define APPEND 2
# define INPUT 4
# define HEREDOC 8
# define FPATH 16
# define PIPE 32
# define OPEN_P 64
# define CLOSE_P 128

# define TRUE 1
# define FALSE 0

# define SINGLE_Q 1
# define DOUEBLE_Q 2

# define C_RESET "\033[0m"
# define C_YELLOW "\033[1;33m"
# define C_BLUE "\033[1;34m"
# define C_RED "\033[1;32m"
# define C_GREEN "\033[1;32m"
# define C_WHITE "\033[1;37m"

#endif
