/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/26 20:25:14 by tliangso         ###   ########.fr       */
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
	int				quote;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_envar
{
	char			*envar;
	struct s_envar	*next;
	struct s_envar	*prev;
}	t_envar;
typedef struct s_runner
{
	int		i;
	int		j;
	char	c;
	char	*deqstr;
}	t_runner;
typedef struct s_env
{
	t_token	*token;
	t_token	*cur_token;
	t_envar	*envar;
}	t_env;

//lexer.c
int		lexer(char *input, t_env *env);
int		lexer_spliter(char *line, t_env *env);
int		pre_sanitise(t_env *env);
void	type_check(t_env *env);

//lexer utils
int		ignore_sep(char *str, int i);
void	check_ignore(char *str, int *sep);
int		is_special_char(char c);
int		has_special_char(char *str);
int		find_special(char *str);
int		quote_cleaner(t_env *env);
void	bracket_cleaner(t_env *env);

//libft.c
int		ft_isspace(char c);
char	*ft_strndup(char *s, int size);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(char *content, int type);
void	ft_tokenprint(t_token *token, int mode, char *color);
int		ft_tokenclear(t_token **lst);
int		ft_tokensize(t_token *lst);
void	ft_tokenadd_front(t_token **lst, t_token *new);
int		ft_tokeninsert(t_token **head, t_token *new, int index);
void	ft_tokendelone(t_token *token);
void	ft_tokenremove(t_token *head, int index);
void	ft_tokenremove_if(t_token *begin_list,
			void *data_ref, int (*cmp)(char *, int));
void	ft_tokendel(t_token *token);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s);
int		ft_strlen(char *s);
int		ft_strchr(char *s, int c);
void	ft_envdelone(t_envar *envar);
void	ft_envremove(t_envar *envar);
t_envar	*ft_envnew(char *key, char *val);
char	*ft_envget(t_envar *envar, char *key);
void	ft_envunset(t_envar *envar, char *key);
void	ft_envadd_back(t_envar **lst, t_envar *new);
int		ft_envclear(t_envar **lst);
void	ft_envprint(t_envar *envar, int mode, char *color);
char	**ft_split(char const *s, char c);
void	ft_envexport(t_envar *envar, char *token);

#endif
