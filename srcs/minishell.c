/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:25:25 by aech-chi          #+#    #+#             */
/*   Updated: 2024/11/12 21:06:37 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "sys/wait.h"
#include <stdbool.h>
#include <limits.h>

t_alloc	*g_allocs = NULL;

int		built_in(int op, t_data *data, t_token *token);
int		unset(t_data *data, t_token *token);

bool	invalid_number(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (true);
		i++;
	}
	return (false);
}

void	set_custom_env(t_data *data)
{
	t_lst	*head;
	char	buffer[1024];
	char	*pwd;

	pwd = getcwd(buffer, 1024);
	head = new_list("OLDPWD", 7);
	head->value = NULL;
	head->next = new_list("PWD", 4);
	head->next->value = new_list(pwd, ft_strlen(pwd));
	head->next->next = new_list("SHLVL", 6);
	head->next->next->value = new_list("1", 2);
	data->env_lst = head;
}

void	set_data_variables(t_data *data, char **envp)
{
	data->envp = envp;
	data->words_count = 1;
	data->flag = 0;
	data->env_lst = NULL;
	if (env_to_lst(envp, data) == 0)
		set_custom_env(data);
	data->env_lst->status = 0;
	data->env = NULL;
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
		if (check_builtin(data.line, &data, envp) != 0)
			continue ;
		fork_main(&data, envp);
		free_allocs(&g_allocs);
	}
	free_data_variables(&data, 0);
	return (0);
}
