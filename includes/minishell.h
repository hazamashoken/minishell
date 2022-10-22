/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/22 21:43:44 by tliangso         ###   ########.fr       */
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

typedef struct s_token
{
	char			*token;
	int				type;
	int				piority;
	struct s_token	*next;
	struct s_token	*prev;
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
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
