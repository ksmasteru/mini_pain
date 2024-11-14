/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:23:00 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:30:14 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"

int	ft_strcmp(char *s1, char *s2);

bool	is_nvalid_arg(t_slice *slice)
{
	if ((slice->location)[0] == '=' || slice->location[0] == 0
		|| ((!ft_isalpha(slice->location[0]) && slice->location[0] != '_')))
		return (true);
	return (false);
}

int	find_key(t_slice *slice)
{
	int	i;

	i = 0;
	if (is_nvalid_arg(slice))
	{
		write(2, "export: `", 10);
		i = -1;
		while (++i < (int)slice->lenght)
			write(2, (slice->location) + i, 1);
		write(2, "': not a valid identifier\n", 27);
		return (-1);
	}
	else
	{
		while (i < (int)slice->lenght)
		{
			if ((slice->location)[i] == '=')
				break ;
			i++;
		}
	}
	return (i);
}

int	find_value(t_slice *location, int key)
{
	if ((location->location)[key] == '=')
		return (1);
	else
		return (-1);
}

void	free_tlst(t_lst **node)
{
	t_lst	*tmp;

	tmp = *node;
	if (!tmp)
		return ;
	if (tmp->data)
		free(tmp->data);
	free(tmp);
	*node = NULL;
}

int	swap_if_key(t_lst **head, t_lst *pair)
{
	t_lst	*tmp;
	t_lst	*swap;

	if (!pair)
		return (-1);
	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(tmp->data, pair->data) == 0)
		{
			if (pair->value)
			{
				swap = tmp->value;
				tmp->value = pair->value;
				free_tlst(&swap);
			}
			else
				free_tlst(&pair->value);
			free_tlst(&pair);
			return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}
