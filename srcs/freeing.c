/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:24:04 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:24:14 by aech-chi         ###   ########.fr       */
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

void	free_t_lst(t_data *data)
{
	t_lst	*holder;
	t_lst	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		holder = tmp->next;
		if (tmp->data)
			free(tmp->data);
		if (tmp->value)
		{
			if (tmp->value->data)
				free(tmp->value->data);
			free(tmp->value);
		}
		free(tmp);
		tmp = holder;
	}
}

void	free_data_variables(t_data *data, int flag)
{
	int		i;
	int		status;

	status = data->env_lst->status;
	i = 0;
	free_t_lst(data);
	if (data->env)
	{
		while (data->env[i])
			free(data->env[i++]);
		free(data->env[i]);
		free(data->env);
	}
	free_allocs(&g_allocs);
	if (g_allocs)
	{
		free(g_allocs->addr);
		free(g_allocs);
	}
	if (flag == 0)
		exit_empty(status);
}

void	alloc_addback(t_alloc **head, void *add)
{
	t_alloc	*tmp;
	t_alloc	*new;

	new = malloc(sizeof(t_alloc));
	new->addr = add;
	new->next = NULL;
	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_allocs(t_alloc **allocs)
{
	t_alloc	*tmp;
	t_alloc	*holder;

	if (!allocs || !*allocs)
		return ;
	tmp = *allocs;
	tmp = tmp->next;
	while (tmp)
	{
		holder = tmp->next;
		free(tmp->addr);
		free(tmp);
		tmp = holder;
	}
	if (*allocs)
		(*allocs)->next = NULL;
}
