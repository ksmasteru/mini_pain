/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_v3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:27:34 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:27:50 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/tokens.h"

void	merge_words(t_token **current, t_token **next)
{
	t_token	*new_next;
	t_token	*tmp;

	new_next = (*next)->next;
	tmp = (*current);
	while (tmp->up)
		tmp = tmp->up;
	tmp->up = *next;
	(*next)->up = NULL;
	(*current)->next = new_next;
}

void	make_redirection_token(t_token **token, t_token *next)
{
	t_token	*tmp;

	tmp = (*token)->next->next;
	(*token)->up = next;
	if ((*token)->type == TO)
		(*token)->up->type = OUT_FILE;
	else if ((*token)->type == APPEND)
		(*token)->up->type = APPEND_FILE;
	else if ((*token)->type == FROM)
		(*token)->up->type = IN_FILE;
	else if ((*token)->type == HEREDOC)
		((*token)->up->type = DELIMETER);
	(*token)->type = REIDRECTION;
	(*token)->up->up = NULL;
	(*token)->next = tmp;
}

void	tokens_v2(t_token **tokens, t_data *data)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->next != NULL)
		{
			if ((tmp->type >= FROM && tmp->type <= APPEND)
				&& tmp->next->type == WORD)
			{
				make_redirection_token(&tmp, tmp->next);
				continue ;
			}
			if (tmp->type == WORD && tmp->next->type == WORD)
			{
				merge_words(&tmp, &(tmp->next));
				continue ;
			}
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	improve_tokens(tokens, data);
}

void	ft_list_add_back(t_token **head, t_token *new)
{
	t_token	*temp;

	temp = *head;
	if (temp == NULL)
	{
		*head = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	if (new != NULL)
		temp->next->next = NULL;
}

void	merge_all_words(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp->next)
	{
		if (tmp->type == WORD && tmp->next->type == WORD)
			merge_words(&tmp, &(tmp->next));
		else
			break ;
	}
}
