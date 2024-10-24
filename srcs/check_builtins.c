/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:20:02 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:21:12 by aech-chi         ###   ########.fr       */
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
	if (!line)/*was || line[0] == 0*/
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
/*this only support word counnt == 1*/
void	dispatach_builtin(int n, t_data *data, char *line)
{
	if (n == 1)
		data->env_lst->status = export(data, data->tokens, line);
	if (n == 2)
		data->env_lst->status = unset(data, data->tokens, line);
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
}

int	check_builtin(char *line, t_data *data)
{
	int	n;

	data->words_count = 1;
	data->tokens = lexer(line, data->env_lst);
	//test_tokens(data->tokens);
	//return 1;
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
