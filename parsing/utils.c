/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:18:23 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:18:42 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

void	pop_error(int exit_code, char *str)
{
	(void)exit_code;
	ft_putstr_fd(2, str);
}

void	free_ls(t_token **token, int direction)
{
	t_token	*tmp;
	t_token	*holder;

	tmp = *token;
	while (tmp)
	{
		if (direction == 1)
			holder = tmp->next;
		else if (direction == 2)
			holder = tmp->up;
		else
			holder = tmp->down;
		if (tmp->location.is_malloced)
		{
			printf("trying to free %s\n", tmp->location.location);
			free(tmp->location.location);
		}
		free(tmp);
		tmp = holder;
	}
	*token = NULL;
}

void	free_ls_2(t_token *token, int direction)
{
	t_token	*tmp;
	t_token	*holder;

	tmp = token;
	while (tmp)
	{
		if (direction == 1)
			holder = tmp->up;
		else if (direction == 2)
			holder = tmp->down;
		if (tmp->location.is_malloced)
			free(tmp->location.location);
		free(tmp);
		tmp = holder;
	}
}

void	free_tokens(t_tree *tree)
{
	if (tree->token)
	{
		free_ls(&(tree->token->up), 2);
		free_ls(&(tree->token->down), 3);
	}
}

void	_free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->fdx[i])
		free(data->fdx[i++]);
	free(data->fdx);
	free(data->pids);
}
