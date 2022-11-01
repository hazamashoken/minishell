/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/11/01 13:14:18 by abossel          ###   ########.fr       */
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

//expander
int		match_wildcard(char *filename, char *pattern);
int		expand_wildcard_tokens(t_env *env);
char    *expand_error(char *token, char *pos, char **next_pos);
char    *expand_brace(char *token, char *pos, char **next_pos);
char    *expand_var(char *token, char *pos, char **next_pos);
int		expand_variable_tokens(t_env *env);
int 	expand_parentheses_tokens(t_env *env);
int		expand_set_priority(t_env *env);
int		expand_check_grammer(t_env *env);
int		expand_get_highest_priority(t_env *env, t_token **start, t_token **end);

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
int		ft_tokeninject(t_token *token, t_token *new_front);
int		ft_tokenadd_after(t_token *token, t_token *after);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s);
int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
