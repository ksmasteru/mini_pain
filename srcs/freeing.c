/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:24:04 by aech-chi          #+#    #+#             */
/*   Updated: 2024/11/12 21:06:13 by hes-saqu         ###   ########.fr       */
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

void	free_tlst_node(t_lst *node)
{
	if (node->data)
		free(node->data);
	if (node->value)
	{
		if (node->value->data)
			free(node->value->data);
		free(node->value);
	}
	free(node);
}

void	free_t_lst(t_lst *head)
{
	t_lst	*holder;

	while (head)
	{
		holder = head->next;
		free_tlst_node(head);
		head = holder;
	}
}

void	free_data_variables(t_data *data, int flag)
{
	int		status;

	status = data->env_lst->status;
	free_t_lst(data->env_lst);
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
