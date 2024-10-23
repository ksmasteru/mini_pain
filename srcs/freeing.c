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

void	free_data_variables(t_data *data, int flag)
{
	t_lst	*tmp;
	t_lst	*holder;
	int		i;
	int status;

	status = data->env_lst->status;
	i = 0;
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
	while (data->env[i])
		free(data->env[i++]);
	free(data->env[i]);
	free(data->env);
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

	tmp = *allocs;
	while (tmp)
	{
		holder = tmp->next;
		free(tmp->addr);
		free(tmp);
		tmp = holder;
	}
	*allocs = NULL;
}
