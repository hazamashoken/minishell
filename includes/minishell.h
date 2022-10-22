/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/22 16:12:14 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "minishell_define.h"

typedef int	t_fd;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	t_token	*token;

}	t_env;

//lexer.c
int		lexer(char *input, t_env *env);

//libft.c
int		ft_isspace(char c);
char	*ft_strndup(const char *s, int size);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(char *content, int type);
void	ft_tokenprint(t_env *env);
int		ft_tokenclear(t_token **lst);
int		ft_tokensize(t_token *lst);
void	ft_tokenadd_front(t_token **lst, t_token *new);
int		ft_tokeninsert(t_token *head, t_token *new, int index);

#endif
