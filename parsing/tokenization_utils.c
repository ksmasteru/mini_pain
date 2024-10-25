/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:17:04 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:18:06 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

t_token_type	decode_type(char *start)
{
	if (*start == '|')
		return (PIPE);
	else if (*start == '<' && *(start + 1) == '<')
		return (HEREDOC);
	else if (*start == '<')
		return (FROM);
	else if (*start == '>' && *(start + 1) == '>')
		return (APPEND);
	else if (*start == '>')
		return (TO);
	else if (*start == '(')
		return (PAREN_L);
	else if (*start == ')')
		return (PAREN_R);
	else if (*start == ';')
		return (SEMICOLON);
	else if (*start == '&' && *(start + 1) == '&')
		return (AND);
	else if (*start == '&')
		return (AMPER);
	else
		return (WORD);
}

void	set_alloc_flag(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->location.is_malloced = true;
}

char	*tokenized_quoted_word(char **str, char *start, t_lst *env_lst,
		t_token **head)
{
	char	*new_word;
	char	*word_before_quotes;
	char	*complete_word;

	word_before_quotes = word_till_quotes(start, env_lst, *head);
	while (**str)
	{
		if (**str == 34 || **str == 39)
			break ;
		*str = *str + 1;
	}
	new_word = make_quoted_word(str, *start, env_lst, *head);
	complete_word = join_and_free(word_before_quotes, new_word);
	if (complete_word && complete_word[0] == 0)
		new_word_token(head, str, complete_word, 1);
	new_word_token(head, str, complete_word, ft_strlen(complete_word));
	if (complete_word)
		set_alloc_flag(head);
	return (complete_word);
}

int	check_balanced_quotes(char *str)
{
	int	starting_quotes;
	int	s_char;

	while (*str && *str != 34 && *str != 39)
		str++;
	starting_quotes = 1;
	s_char = *str++;
	while (*str != '\0')
	{
		if ((*str == 34 || *str == 39) && starting_quotes == 0)
		{
			s_char = *str++;
			starting_quotes++;
			continue ;
		}
		if (*str++ == s_char)
		{
			if (++starting_quotes == 2)
				starting_quotes = 0;
		}
	}
	if (starting_quotes == 0)
		return (0);
	return (1);
}

void	split_add_to_env(char *new_word, t_token **head, char **str)
{
	int		i;
	char	**splitted;

	i = 0;
	if (!new_word || new_word[0] == 0)
	{
		new_word_token(head, str, new_word, 1);
		return ;
	}
	splitted = ft_split(new_word, 32);
	while (splitted[i])
	{
		alloc_addback(&g_allocs, splitted[i]);
		if (new_word[0] == 0)
			new_word_token(head, str, splitted[i], 1);
		else
			new_word_token(head, str, splitted[i], ft_strlen(splitted[i]));
		set_alloc_flag(head);
		i++;
	}
	alloc_addback(&g_allocs, splitted[i]);
	alloc_addback(&g_allocs, splitted);
}
