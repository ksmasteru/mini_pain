/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:25:25 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:30:52 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "sys/wait.h"
#include <stdbool.h>

t_alloc	*g_allocs = NULL;

int		built_in(int op, t_data *data, t_token *token);
int		unset(t_data *data, t_token *token);

void	set_data_variables(t_data *data, char **envp)
{
	data->envp = envp;
	data->words_count = 1;
	data->flag = 0;
	data->env_lst = NULL;
	env_to_lst(envp, data);
	data->env_lst->status = 0;
	data->env = get_envp(envp);
	data->mem_ref = NULL;
	data->line = NULL;
	data->pwd = NULL;
	data->oldpwd = NULL;
	data->is_cmd = 0;
	ft_strdup2("LOL");
	g_allocs->data = data;
}

void	fork_main(t_data *data, char **envp)
{
	int	exit_status;

	exit_status = parse_cmd(data->line, envp, data);
	data->env_lst->status = exit_status;
	data->line = NULL;
}

void	*_alloc(size_t size, t_alloc **g_allocs)
{
	void	*new_add;

	new_add = malloc(size);
	alloc_addback(g_allocs, new_add);
	return (new_add);
}

void	exit_empty(int status)
{
	write(2, "exit\n", 6);
	exit(status);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	signal(SIGQUIT, SIG_IGN);
	data.ac = ac;
	data.av = av;
	set_data_variables(&data, envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, signal_ctlc);
		data.line = read_cmd();
		if (!data.line)
			break ;
		if (check_builtin(data.line, &data) != 0)
			continue ;
		fork_main(&data, envp);
		free_allocs(&g_allocs);
	}
	free_data_variables(&data, 0);
	return (0);
}
