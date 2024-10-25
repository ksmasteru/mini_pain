/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:16:06 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:16:19 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

t_token	*make_new_node(t_token_type type, char *start, size_t length)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	alloc_addback(&g_allocs, new);
	if (!new)
		return (NULL);
	new->type = type;
	new->location = (t_slice){start, length, false};
	new->next = NULL;
	new->up = NULL;
	new->down = NULL;
	return (new);
}

void	new_word_token(t_token **head, char **str, char *start, size_t length)
{
	t_token			*tmp;
	t_token			*new;
	t_token_type	type;

	if (start == NULL || str == NULL || length == 0)
		return ;
	tmp = *head;
	type = WORD;
	if (*head == NULL)
	{
		*head = make_new_node(type, start, length);
		return ;
	}
	new = make_new_node(type, start, length);
	if (!new)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_new_token(t_token **head, char **str, char *start, size_t length)
{
	t_token			*tmp;
	t_token			*new;
	t_token_type	type;

	if (start == NULL || str == NULL)
		return ;
	tmp = *head;
	type = decode_type(start);
	if (type == HEREDOC || type == APPEND || type == AND)
		*str = *str + 2;
	else if (type != WORD)
		*str = *str + 1;
	if (*head == NULL)
	{
		*head = make_new_node(type, start, length);
		return ;
	}
	new = make_new_node(type, start, length);
	if (!new)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
