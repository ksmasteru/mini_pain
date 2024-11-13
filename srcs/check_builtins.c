/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:20:02 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:29:49 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "sys/wait.h"
#include <stdbool.h>

extern t_alloc	*g_allocs;

int	built_in_code2(char *line)
{
	if (ft_strlen(line) >= 3)
	{
		if (ft_strncmp("env", line, 3) == 0 && (ft_strchr(" \v\t\n", line[3])
				|| line[3] == 0))
			return (3);
		if (ft_strncmp("pwd", line, 3) == 0 && (ft_strchr(" \v\t\n", line[3])
				|| line[3] == 0))
			return (4);
	}
	if (ft_strlen(line) >= 2)
	{
		if (ft_strncmp("cd", line, 2) == 0 && (ft_strchr(" \v\t\n", line[2])
				|| line[2] == 0))
			return (5);
	}
	return (0);
}

int	built_in_code(char *line)
{
	if (!line)
		exit(0);
	if (ft_strlen(line) >= 6)
	{
		if (ft_strncmp("export", line, 6) == 0 && (ft_strchr(" \v\t\n", line[6])
				|| line[6] == 0))
			return (1);
	}
	if (ft_strlen(line) >= 5)
	{
		if (ft_strncmp("unset", line, 5) == 0 && (ft_strchr(" \v\t\n", line[5])
				|| line[5] == 0))
			return (2);
	}
	if (ft_strlen(line) >= 4)
	{
		if (ft_strncmp("echo", line, 4) == 0 && (ft_strchr(" \v\t\n", line[4])
				|| line[4] == 0))
			return (6);
		if (ft_strncmp("exit", line, 4) == 0 && (ft_strchr(" \v\t\n", line[4])
				|| line[4] == 0))
			return (7);
	}
	return (built_in_code2(line));
}

void	dispatach_builtin(int n, t_data *data, char *line)
{
	data->flag = manage_redirections(data->tokens->down, data);
	if (data->flag == -1)
		return ;
	if (n == 1)
		data->env_lst->status = export(data, data->tokens->up);
	if (n == 2)
		data->env_lst->status = unset(data, data->tokens);
	if (n == 3)
		data->env_lst->status = show_env(data, 0);
	if (n == 4)
		data->env_lst->status = pwd(line, data->tokens, data);
	if (n == 5)
		data->env_lst->status = cd(line, data, data->tokens);
	if (n == 6)
		data->env_lst->status = ft_echo2(data, line, data->tokens);
	if (n == 7)
		data->env_lst->status = ft_exit(data, line, data->tokens);
	if (data->flag == 0 || data->flag == 1)
		restore_tty(data->flag);
}

int	check_builtin(char *line, t_data *data, char **envp)
{
	int	n;

	data->envp = envp;
	data->words_count = 1;
	data->tokens = lexer(line, data->env_lst);
	if (!data->tokens || check_syntax_error(&data->tokens) < 0)
	{
		free_allocs(&g_allocs);
		return (1);
	}
	tokens_v2(&data->tokens, data);
	n = built_in_code(line);
	if (n > 0 && data->words_count == 1)
	{
		dispatach_builtin(n, data, line);
		free_allocs(&g_allocs);
		return (1);
	}
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
