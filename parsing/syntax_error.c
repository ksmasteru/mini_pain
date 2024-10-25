/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:16:35 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:27:15 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/tokens.h"

void	write_token(int type)
{
	if (type == PAREN_L)
		write(2, "\'(\'\n", 5);
	else if (type == PAREN_R)
		write(2, "\')\'\n", 5);
	else if (type == OR)
		write(2, "\'||\'\n", 6);
	else if (type == AND)
		write(2, "\'&&\'\n", 6);
	else if (type == SEMICOLON)
		write(2, "\';\'\n", 5);
	else if (type == AMPER)
		write(2, "\'&\'\n", 5);
}

int	syntax_error(int code, t_token **tokens, int type)
{
	(void)tokens;
	(void)type;
	if (code == 1)
		write(2, "parsing error near \'|\' \n", 25);
	else if (code == 2 && type == PIPE)
		write(2, "syntax error: unexpected end of file\n", 37);
	else if (code == 2 && (type >= FROM && type <= APPEND))
		write(2, "syntax error near unexpected token `newline\'\n", 46);
	else if (code == 2)
	{
		write(2, "syntax error near unexpected token ", 36);
		write_token(type);
	}
	return (-1);
}

int	check_syntax_error(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp->type == PIPE)
		return (syntax_error(1, tokens, PIPE));
	else if (tmp->type != WORD && tmp->next == NULL)
		return (syntax_error(2, tokens, tmp->type));
	while (tmp->next)
	{
		if (tmp->type == PIPE)
		{
			if (tmp->next->type == PIPE)
				return (syntax_error(2, tokens, tmp->type));
		}
		if (tmp->type >= 6 && tmp->type <= 9)
		{
			if (tmp->next->type != WORD)
				return (syntax_error(2, tokens, tmp->type));
		}
		tmp = tmp->next;
	}
	if (tmp->type != WORD)
		return (syntax_error(2, tokens, tmp->type));
	return (0);
}

void	ft_list_addback(t_token **head, t_token *new)
{
	t_token	*tmp;
	t_token	*new_next;

	if (new != NULL)
		new_next = new->next;
	tmp = *head;
	if (!new)
		return ;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp->next->next = new_next;
}

void	free_lst(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens);
		tokens = tmp;
	}
}
