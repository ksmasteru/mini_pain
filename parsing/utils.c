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

void	_free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->fdx[i])
		free(data->fdx[i++]);
	free(data->fdx);
	free(data->pids);
}
