/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_v2.c                                        :+:      :+:    :+:   */
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

void	merge_the_redirections(t_token **redirection_list, t_token *new_red)
{
	t_token	*tmp;

	tmp = *redirection_list;
	if (!tmp)
	{
		*redirection_list = new_red;
		return ;
	}
	if (!tmp->down)
		tmp->down = new_red;
	else
	{
		while (tmp->down)
			tmp = tmp->down;
		tmp->down = new_red;
		tmp->down->down = NULL;
	}
}

t_token	*merge_simple_command(t_token **words_list, t_token **redirection_list)
{
	t_token	*simple_command;

	if (*words_list != NULL)
	{
		(*words_list)->down = *redirection_list;
		(*words_list)->next = NULL;
		simple_command = *words_list;
	}
	else
		simple_command = *redirection_list;
	return (simple_command);
}

t_token	*tokens_v6(t_token **tokens)
{
	t_token	*tmp;
	t_token	*redirection_list;
	t_token	*words_list;
	t_token	*shunk;

	redirection_list = NULL;
	words_list = NULL;
	tmp = *tokens;
	while (tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			merge_the_words(&words_list, tmp);
		else if (tmp->type == REIDRECTION)
			merge_the_redirections(&redirection_list, tmp);
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	shunk = merge_simple_command(&words_list, &redirection_list);
	*tokens = tmp;
	return (shunk);
}

void	improve_tokens(t_token **tokens, t_data *data)
{
	t_token	*shunk;
	t_token	*final_list;

	final_list = NULL;
	while ((*tokens) != NULL)
	{
		shunk = tokens_v6(tokens);
		if (shunk != NULL)
			shunk->next = NULL;
		ft_list_addback(&final_list, shunk);
		if (*tokens == NULL)
			break ;
		if ((*tokens)->type == PIPE)
		{
			data->words_count++;
			ft_list_addback(&final_list, (*tokens));
			*tokens = (*tokens)->next;
		}
	}
	*tokens = final_list;
}
