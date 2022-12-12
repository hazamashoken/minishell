/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:22 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/12 15:09:42 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free_n(char *s1, char *s2, int n)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (n == 1 && s1)
		free(s1);
	else if (n == 2 && s2)
		free(s2);
	else if (n == 3)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
	return (ret);
}

char	*prompt(void)
{
	char	*cwd;
	char	*home;
	char	*name;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	home = getenv("HOME");
	name = getenv("USER");
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		cwd = tmp;
	}
	cwd = ft_strjoin_free_n("\033[30;1;7m\033[47m ", cwd, 2);
	cwd = ft_strjoin_free_n(cwd, " | ", 1);
	cwd = ft_strjoin_free_n(cwd, name, 1);
	cwd = ft_strjoin_free_n(cwd, " \033[0m \n\u00AB\0", 1);
	return (cwd);
}

void	tri_array_free(char	***array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_split_free(array[i]);
		i++;
	}
	free(array);
}

void	ft_print_3array(char ***array)
{
	int	i;
	int	j;

	i = 0;
	if (array)
	{
		printf("%p\n", array);
		if (*array)
		{
			printf("*%p\n", *array);
			if (**array)
				printf("**%p\n", **array);

		}
	}
	while (array[i])
	{
		j = 0;
		while (array[i][j])
			printf("%s\n", array[i][j++]);
		printf("====\n");
		i++;
	}
}

int	main(void)
{
	t_env	env;
	char	*input;
	char	*inprompt;

	minishell_init(&env);
	printf("\e[1;1H\e[2J");
	printf("pid: %d\n", getpid());
	while (1)
	{
		inprompt = prompt();
		input = readline(inprompt);
		free(inprompt);
		if (input == NULL)
			break ;
		add_history(input);
		if (lexer(input, &env))
			continue ;
		if (parser(&env))
			continue ;
		printf("%p\n", *env.files);
		ft_print_3array(env.files);
		ft_print_3array(env.pipex_cmds);
		ft_tokenprint(env.token, -1, C_GREEN);
		//executor(&env);
		ft_tokenclear(&env.token);
		tri_array_free(env.pipex_cmds);
		tri_array_free(env.files);
	}
	printf("\nexit\n");
	minishell_end(&env);
	return (0);
}
