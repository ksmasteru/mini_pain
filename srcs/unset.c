/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:26:25 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:27:00 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <stdio.h>

bool	not_valid_variable(t_token *token)
{
	char	*str;
	int		i;

	i = 0;
	str = token->location.location;
	if (str[token->location.lenght] != 0)
		str[token->location.lenght] = 0;
	if (is_empty(str))
		return (true);
	if (*str == 0 || (*str >= '0' && *str <= '9'))
		return (true);
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')
				|| str[i] == '_'))
			return (true);
		i++;
	}
	return (false);
}

int	unset_error(t_token *token)
{
	write(2, "minishell: ", 12);
	write(2, "unset: ", 8);
	if (token->location.location[0] != 0)
		token->location.location[token->location.lenght] = 0;
	write(2, "`", 2);
	ft_putstr_fd(2, token->location.location);
	write(2, "\':", 3);
	write(2, " not a valid identifier\n", 24);
	return (1);
}

void	ft_lstdelete(t_lst **head, t_lst *to_delete)
{
	t_lst	*tmp;
	t_lst	*holder;

	if (!head || !*head || !to_delete)
		return ;
	tmp = *head;
	holder = to_delete->next;
	while (tmp->next && tmp->next != to_delete)
		tmp = tmp->next;
	if (!tmp)
		return ;
	tmp->next = holder;
	free_tlst_node(to_delete);
}

int	unset(t_data *data, t_token *token)
{
	t_lst	*tmp;
	int		code;
	t_lst	*holder;

	if (token->up == NULL)
		return (0);
	token = token->up;
	while (token)
	{
		tmp = data->env_lst;
		code = 0;
		if (token->location.location[0] == 0 || not_valid_variable(token))
			code = unset_error(token);
		while (tmp && code != 1)
		{
			holder = tmp->next;
			if (ft_strncmp(tmp->data, token->location.location,
					token->location.lenght) == 0)
				ft_lstdelete(&(data->env_lst), tmp);
			tmp = holder;
		}
		token = token->up;
	}
	return (code);
}

t_mini	*mini(void)
{
	static t_mini	var;

	return (&var);
}
