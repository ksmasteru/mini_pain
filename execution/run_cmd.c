/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:00:56 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/11/12 21:04:32 by hes-saqu         ###   ########.fr       */
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

int	init_check_main_cmd(t_data *data, t_token *token)
{
	if (token->type == WORD)
		data->flag = manage_redirections(token->down, data);
	else if (token->type == REIDRECTION)
		data->flag = manage_redirections(token, data);
	if (data->is_cmd == -1)
	{
		close_all_pipes(data->fdx, data->words_count);
		return (127);
	}
	else if (data->flag == -1 || data->words_count != 1)
		close_and_dup2(data->fdx, data->index, data->words_count,
			data->flag);
	return (0);
}

int	run_cmd_main(char **args, char *cmd, t_token *token, t_data *data)
{
	int	status;

	status = 0;
	data->pids[data->words_count - 1] = fork();
	if (data->pids[data->words_count - 1] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status = init_check_main_cmd(data, token);
		if (built_in_code(cmd) != 0)
			check_builtin_multiple(cmd, data, token, built_in_code(cmd));
		_exec_cmd(status, cmd, args, data);
	}
	return (0);
}

void	_exec_cmd(int status, char *cmd, char **args, t_data *data)
{
	if (status == 0)
	{
		execve(cmd, args, data->envp);
		if (errno == ENOENT)
			status = 127;
		else
			status = 126;
		print_error_errno("minishell", cmd, NULL);
	}
	else
		print_cmd_nfound(cmd);
	free_data_variables(data, 1);
	exit(status);
}

int	execute_cmd(int index, int len, t_data *data, t_token *token)
{
	int				status;
	char			**args;
	char			*cmd;

	data->index = index;
	set_exec_args(token, data, &args, &cmd);
	if (index == len - 1 || len == 1)
		return (run_cmd_main(args, cmd, token, data));
	data->pids[index] = fork();
	if (data->pids[index] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status = init_exec_check(token, data, index);
		if (built_in_code(cmd) != 0)
			check_builtin_multiple(cmd, data, token, built_in_code(cmd));
		_exec_cmd(status, cmd, args, data);
	}
	return (0);
}

void	run_cmd(int len, t_data *data)
{
	t_token	*tmp;
	int		index;

	index = 0;
	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type != PIPE)
			execute_cmd(index++, len, data, tmp);
		tmp = tmp->next;
	}
}
