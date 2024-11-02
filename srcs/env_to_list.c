/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:21:24 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:22:49 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern t_alloc	*g_allocs;

t_lst	*new_lst(char *str, int len)
{
	t_lst	*new_node;

	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_lst));
	new_node->data = (char *)malloc(sizeof(char) * len + 1);
	alloc_addback(&g_allocs, new_node->data);
	alloc_addback(&g_allocs, new_node);
	new_node->data[len] = '\0';
	new_node->data = strncpy(new_node->data, str, len);
	new_node->next = NULL;
	new_node->value = NULL;
	return (new_node);
}

t_lst	*new_list(char *str, int len)
{
	t_lst	*new_node;

	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_lst));
	new_node->data = (char *)malloc(sizeof(char) * len + 1);
	new_node->data[len] = '\0';
	new_node->data = strncpy(new_node->data, str, len);
	new_node->next = NULL;
	new_node->value = NULL;
	return (new_node);
}

void	lst_addback(t_lst **head, t_lst *new_lst)
{
	t_lst	*tmp;

	if (*head == NULL)
	{
		*head = new_lst;
		return ;
	}
	else
		tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_lst;
}

t_lst	*get_pair(char *str)
{
	int		i;
	t_lst	*pair;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '\n')
		i++;
	pair = new_list(str, i);
	if (str[i] != '=')
		pair->value = NULL;
	else
	{
		pair->value = new_list(str + i + 1, ft_strlen(str + i + 1));
	}
	return (pair);
}

int	env_to_lst(char **env, t_data *data)
{
	int		i;
	t_lst	*pair;

	i = 0;
	while (env[i])
	{
		pair = get_pair(env[i]);
		add_val_to_env(pair, data);
		i++;
	}
	return (i);
}
