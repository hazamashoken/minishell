/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/29 20:52:15 by tliangso         ###   ########.fr       */
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
# include <errno.h>

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
	int		ret;
	int		exit;
	char	**tmp_environ;
	char	**dup_environ;
}	t_env;

extern char	**environ;

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

//built-in
int		mini_echo(char **args);
void	mini_pwd(t_env *env);
int		args_len(char **args);
void	mini_env(void);
void	mini_unset(char **args);
void	mini_cd(t_env *env, char **args);
void	mini_export(char **args);

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
char	*ft_strchr(char *s, int c);
void	ft_envdelone(t_envar *envar);
void	ft_envremove(t_envar *envar);
t_envar	*ft_envnew(char *envar);
char	*ft_envget(t_envar *envar, char *key);
void	ft_envunset(t_envar *envar, char *key);
void	ft_envadd_back(t_envar **lst, t_envar *new);
int		ft_envclear(t_envar **lst);
void	ft_envprint(t_envar *envar, int mode, char *color);
char	**ft_split(char const *s, char c);
void	ft_envexport(t_envar *envar, char *token);
int		ft_putstr_fd(char *str, int fd);
int		ft_atoi(const char *nptr);
void	error_put( t_env *env, char *str, char *args, int sig);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_free(char *s1, char *s2, int mode);
void	ft_free_split(char	**args);
int		ft_split_size(char	**split);
char	**ft_split_addback(char **words, char *string);
char	**ft_split_dup(char **words);
void	ft_split_free(char **words);
int		ft_strunspn(char *str, char *reject);
int		ft_strlcmpchr(char *s1, char *s2, char c);

#endif
