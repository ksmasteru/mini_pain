/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:24:06 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/25 00:25:12 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

void	run_multiple_commands(t_data *data)
{
	int	*pids;
	int	**pfd;
	int	i;

	i = 0;
	pids = (int *)malloc(sizeof(int) * (data->words_count));
	alloc_addback(&g_allocs, pids);
	pfd = (int **)malloc(sizeof(int *) * data->words_count - 1);
	alloc_addback(&g_allocs, pfd);
	while (i < data->words_count - 1)
	{
		pfd[i] = (int *)malloc(sizeof(int) * 2);
		alloc_addback(&g_allocs, pfd[i++]);
	}
	fill_pipes(&pfd, data->words_count - 1);
	data->fdx = pfd;
	data->pids = pids;
	if (data->words_count > 1)
		run_cmd(data->words_count, data);
	else
		execute_cmd(0, 1, data, data->tokens);
}

int	parse_cmd(char *line, char **envp, t_data *data)
{
	int	status;
	int	pid;

	signal(SIGINT, SIG_IGN);
	status = 0;
	data->envp = envp;
	data->flag = 0;
	data->line = line;
	pid = 0;
	run_multiple_commands(data);
	close_all_pipes(data->fdx, data->words_count);
	waitpid(data->pids[data->words_count - 1], &status, 0);
	while (pid >= 0)
		pid = wait(NULL);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			write(2, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == 2)
			write(2, "\n", 2);
		status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
