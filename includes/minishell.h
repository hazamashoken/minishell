/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 21:27:34 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <term.h>

# include "minishell_define.h"
# include "pipex.h"
# include "get_next_line.h"
// # include "libft.h"

typedef struct s_token
{
	char			*token;
	int				type;
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

typedef struct s_term
{
	struct termios	minishell;
	struct termios	shell;
}	t_term;

typedef struct s_env
{
	t_token				*token;
	t_token				*cur_token;
	char				***pipex_cmds;
	char				***files;
	int					ret;
	int					exit;
	int					cmd_counts;
	char				**tmp_environ;
	char				**dup_environ;
	t_term				*term;
	struct sigaction	sigint;
	struct sigaction	sigquit;

}	t_env;

extern char	**environ;

//parser.c
int		run_pipex(t_env *env);
int		parser(t_env *env);
int		args_exec(t_env *env, t_process **procs);

//lexer.c
int		lexer(char *input, t_env *env);
int		lexer_spliter(char *line, t_env *env);
int		pre_sanitise(t_env *env);
int		type_check(t_env *env);

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
int		mini_pwd(void);
int		args_len(char **args);
int		mini_env(void);
int		mini_unset(char **args);
int		mini_cd(char **args);
int		mini_export(t_env *env, char **args);
int		mini_exit(t_env *env, char **args);

//init_minishell.c
int		minishell_init(t_env *env);
void	minishell_end(t_env *env);

//expander
int		match_wildcard(char *filename, char *pattern);
int		expand_wildcard_tokens(t_env *env);
char	*expand_error(t_env *env, char *token, char *pos, char **next_pos);
char	*expand_brace(char *token, char *pos, char **next_pos);
char	*expand_var(char *token, char *pos, char **next_pos);
int		expand_variable_tokens(t_env *env);
int		expand_parentheses_tokens(t_env *env);
int		expand_set_priority(t_env *env);
int		expand_check_grammer(t_env *env);
int		expand_get_highest_priority(t_env *env, t_token **start, t_token **end);

//libft.c
char	*ft_itoa(int n);
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
int		ft_strlen(const char *s);
char	*ft_strchr(char *s, int c);
char	**ft_split(char const *s, char c);
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
int		ft_tokeninject(t_token *token, t_token *new_front);
int		ft_tokenadd_after(t_token *token, t_token *after);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
