/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:25:58 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/25 01:07:11 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

extern t_alloc	*g_allocs;

int	set_exec_args(t_token *token, t_data *data, char ***args, char **cmd)
{
	data->flag = 0;
	data->is_cmd = 0;
	if (token->type == REIDRECTION)
	{
		*args = NULL;
		*cmd = NULL;
	}
	else
	{
		*args = get_word_args(token);
		if (!*args)
			perror("args");
		*cmd = get_path(data, *args[0]);
		if (*cmd && is_builtin(*cmd) == 0 && !ft_strchr(*cmd, '/'))
			data->is_cmd = -1;
	}
	return (0);
}

int	init_exec_check(t_token *head, t_data *data, int index)
{
	if (head->type == WORD)
		data->flag = manage_redirections(head->down, data);
	else if (head->type == REIDRECTION)
		data->flag = manage_redirections(head->down, data);
	if (data->is_cmd == -1)
	{
		close_all_pipes(data->fdx, data->words_count);
		return (127);
	}
	close_and_dup2(data->fdx, index, data->words_count, data->flag);
	return (0);
}

char	*slice_and_dice(t_slice slice)
{
	char	*res;

	res = malloc(sizeof(char) * (slice.lenght + 1));
	alloc_addback(&g_allocs, res);
	if (!res)
		return (NULL);
	res[slice.lenght] = '\0';
	strncpy(res, slice.location, slice.lenght);
	return (res);
}

char	**get_word_args(t_token *token)
{
	int		words_number;
	char	**args;
	int		i;
	t_token	*tmp;

	tmp = token;
	i = 0;
	words_number = 0;
	while (tmp)
	{
		words_number++;
		tmp = tmp->up;
	}
	args = (char **)malloc(sizeof(char *) * (words_number + 1));
	alloc_addback(&g_allocs, args);
	while (i < words_number)
	{
		args[i] = slice_and_dice(token->location);
		i++;
		token = token->up;
	}
	args[i] = NULL;
	return (args);
}
// should clear up data as it exits.
int	check_builtin_multiple(char *line, t_data *data, t_token *token, int n)
{
	int status;

	status = 0;
	if (n == 1)
		status = export(data, token->up);
	if (n == 2)
		status = unset(data, token);
	if (n == 3)
		status = show_env(data, 0);
	if (n == 4)
		status = pwd(line, token, data);
	if (n == 5)
		status = cd(line, data, token);
	if (n == 6)
		status = ft_echo2(data, line, token);
	if (n == 7)
		status = ft_exit(data, line, token);
	free_data_variables(data, 1);
	exit(status);
}
