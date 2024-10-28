/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:12:22 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:12:29 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/tokens.h"

void	word_add_down(t_token **word, t_token *redir)
{
	t_token	*tmp;

	(*word)->next = redir->next;
	tmp = (*word)->down;
	if (tmp == NULL)
	{
		(*word)->down = redir;
		redir->next = NULL;
	}
	else
	{
		while (tmp->down)
			tmp = tmp->down;
		tmp->down = redir;
		tmp->down->down = NULL;
	}
}

void	swap_redir_word(t_token **redir, t_token *word)
{
	t_token	*temp;
	t_token	*tmp_dwn;
	t_token	*word_next;

	word_next = word->next;
	temp = *redir;
	tmp_dwn = word->down;
	if (tmp_dwn == NULL)
		word->down = temp;
	else
	{
		while (tmp_dwn->down)
			tmp_dwn = tmp_dwn->down;
		tmp_dwn->down = temp;
	}
	*redir = word;
	(*redir)->next = word_next;
}

void	merge_the_words(t_token **words_list, t_token *new_word)
{
	t_token	*tmp;

	tmp = *words_list;
	if (!tmp)
	{
		*words_list = new_word;
		return ;
	}
	if ((tmp->up) == NULL)
		tmp->up = new_word;
	else
	{
		while (tmp->up)
			tmp = tmp->up;
		tmp->up = new_word;
		tmp->up->up = NULL;
	}
}
