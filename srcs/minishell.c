/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:25:25 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:26:11 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "sys/wait.h"
#include <stdbool.h>

int		allocated = 0;
int		freed = 0;
t_alloc	*g_allocs = NULL;
int		built_in(int op, t_data *data, t_token *token);
int		unset(t_data *data, t_token *token, char *line);

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	if (line[0] == 0)
		return (true);
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == 0 || line[i] == '\n')
		return (true);
	return (false);
}

char	*read_cmd(void)
{
	char	*line;

	while (1)
	{
		line = readline("\e[0;32m[minishell]$ \e[0;0m");
		if (!line)
			return (NULL);
		else if (is_empty(line))
		{
			free(line);
			continue ;
		}
		else
			break ;
	}
	if (access(".tmp.txt", F_OK) == 0)
		unlink(".tmp.txt");
	add_history(line);
	alloc_addback(&g_allocs, line);
	return (line);
}

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
	data->allocs = NULL;
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

void exit_empty(int status)
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
	//rl_clear_history();
	free_data_variables(&data, 0);
	return (0);
}
