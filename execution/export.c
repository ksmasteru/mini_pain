/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:34:15 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/25 01:09:46 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"

void	add_val_to_env(t_lst *pair, t_data *data)
{
	if (!pair)
		return ;
	if (swap_if_key(&(data->env_lst), pair) < 0)
		lst_addback(&(data->env_lst), pair);
}

t_lst	*export_value(t_token *token)
{
	int		key;
	int		value;
	t_lst	*key_val;
	t_lst	*val_val;

	if (token->location.location[0] != 0)
		token->location.location[token->location.lenght] = 0;
	key = find_key(&(token->location));
	if (key == -1)
		return (NULL);
	value = find_value(&(token->location), key);
	if (value == -1)
		val_val = (NULL);
	else
	{
		token->location.location[token->location.lenght] = '\0';
		val_val = new_list((token->location.location + key + 1),
				ft_strlen(token->location.location + key + 1));
	}
	token->location.location[key] = '\0';
	key_val = new_list(token->location.location, key);
	if (val_val)
		key_val->value = val_val;
	return (key_val);
}

int	show_export(t_data *data)
{
	t_lst	*tmp;
	char	c;

	c = 34;
	tmp = data->env_lst;
	while (tmp)
	{
		ft_putstr(1, "declare -x ");
		ft_putstr(1, tmp->data);
		if (tmp->value)
			write(1, "=", 1);
		else
		{
			write(1, "\n", 1);
			tmp = tmp->next;
			continue ;
		}
		write(1, &c, 1);
		if (tmp->value)
			ft_putstr(1, tmp->value->data);
		write(1, &c, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}

int	show_env(t_data *data, int is_export)
{
	t_lst	*tmp;

	if (is_export == 1)
		return (show_export(data));
	tmp = data->env_lst;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr(1, tmp->data);
			write(1, "=", 1);
			ft_putstr(1, tmp->value->data);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	export(t_data *data, t_token *token)
{
	t_lst	*pair;

	if (token == NULL)
		return (show_env(data, 1));
	if (*(token->location.location) == 32 || (*(token->location.location) >= 9
			&& *(token->location.location) <= 13))
	{
		write(2, "export: not valid in this context:\n", 36);
		while (*(token->location.location))
		{
			if (*(token->location.location) != '=')
				write(2, (token->location.location), 1);
			(token->location.location)++;
		}
		return (1);
	}
	while (token)
	{
		pair = export_value(token);
		add_val_to_env(pair, data);
		token = token->up;
	}
	if (!pair)
		return (1);
	return (0);
}
