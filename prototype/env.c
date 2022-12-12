/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:23:58 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 12:04:53 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell_define.h"

extern char	**environ;

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (*(unsigned char *)(s + len) != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	while (*(s + i) != '\0')
	{
		*(str + i) = *(s + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

int	ft_split_size(char	**split)
{
	int	len;

	len = 0;
	while (split[len] != NULL)
		len++;
	return (len);
}

void	ft_split_free(char **words)
{
	int	i;

	if (words != NULL)
	{
		i = 0;
		while (words[i] != NULL)
		{
			free(words[i]);
			i++;
		}
		free(words);
	}
}

char	**ft_split_dup(char **words)
{
	char	**dup;
	int		size;
	int		i;

	if (words == NULL)
		return (NULL);
	size = ft_split_size(words);
	dup = malloc(sizeof(char **) * (size + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(words[i]);
		if (dup[i] == NULL)
		{
			ft_split_free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

char	**ft_split_addback(char **words, char *string)
{
	char	**join;
	int		size;
	int		i;

	if (words == NULL || string == NULL)
		return (NULL);
	size = ft_split_size(words);
	join = malloc(sizeof(char **) * (size + 2));
	if (join == NULL)
		return (NULL);
	join[size] = ft_strdup(string);
	if (join[size] != NULL)
	{
		i = 0;
		while (words[i] != NULL)
		{
			join[i] = words[i];
			i++;
		}
		join[size + 1] = NULL;
		free(words);
		return (join);
	}
	free(join);
	return (NULL);
}

int	ft_putstr_fd(char *str, int fd)
{
	int	len;

	if (fd < 0)
		return (-1);
	len = 0;
	while (str[len])
		len++;
	return (write(fd, str, len));
}

char	*ft_strchr(char *s, int c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (s);
}

int	ft_strunspn(char *str, char *reject)
{
	int	i;

	i = 0;
	while (*(str + i) && !ft_strchr(reject, *(str + i)))
		i++;
	if (i == ft_strlen(str) && ft_strchr(reject, *(str + i)))
		return (-1);
	return (i);
}

int	ft_strspn(char *str, char *accept)
{
	int	i;

	i = 0;
	while (*(str + i) && ft_strchr(accept, *(str + i)))
		i++;
	return (i);
}

int	ft_strlcmpchr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (*(s1 + i) && *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i) || *(s1 + i) == c)
			return (++i);
		i++;
	}
	return (i);
}

void	add_env(char *env)
{
	char	**dup;

	dup = ft_split_dup(environ);
	ft_split_free(environ);
	environ = dup;
	environ = ft_split_addback(dup, env);
	dup = environ;

}

void	reset_env(char *args)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		if (ft_strlcmpchr(environ[i], args, '=')
			== ft_strunspn(environ[i], "=") + 1
			&& ft_strunspn(environ[i], "=")
			== ft_strunspn(args, "="))
		{
			free(environ[i]);
			environ[i] = ft_strdup(args);
			return ;
		}
	}
	add_env(args);
}

int	arg_is_env(char *args, char *env)
{
	int	i;

	i = 0;
	while (args[i] == env[i])
		i++;
	if (args[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

int	unset_env(char *args)
{
	int	i;

	i = -1;
	printf("%strying to unset : %s%s\n",C_YELLOW, args, C_RESET);
	if (ft_strchr(args, '='))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": invalid parameter name\n", 2);
		return (1);
	}
	while (environ[++i])
	{
		if (arg_is_env(args, environ[i]))
		{
			printf("%sunseting : %s%s\n",C_YELLOW, environ[i], C_RESET);
			free(environ[i]);
			environ[i] = ft_strdup("\0");
			return (0);
		}
	}
	return (0);
}

int	main(void)
{
	// t_envar	*envar;
	int		i;
	char	**dup;
	char	**tmp;
	char	*rp;
	char	*del;

	tmp = environ;
	environ = ft_split_dup(environ);
	reset_env("TEST=1");
	reset_env("TEST=2");
	reset_env("TEST=3");
	reset_env("TESTS=4");
	reset_env("TESTS=5");
	reset_env("TESTS=6");
	reset_env("TEST=7");
	reset_env("TESTS=8");
	unset_env("TEST");
	unset_env("TESTS=");




	i = -1;
	while (environ[++i])
		// if (environ[i][0] != '_' && environ[i][0] != '\0' && environ[i][1] != '=')
			printf("%s\n", environ[i]);
	// printf("_=%s\n", getenv("_"));
	//printf("env : %s\n", getenv("TEST"));
	ft_split_free(environ);
	environ = tmp;
	// i = -1;
	// while (environ[++i])
	// 	printf("%s\n", environ[i]);
	// printf("env : %s\n", getenv("TEST"));
	return (0);
}
