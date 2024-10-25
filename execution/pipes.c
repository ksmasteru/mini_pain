/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:47:00 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/25 01:17:54 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

extern t_alloc	*g_allocs;

int	fill_pipes(int ***p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipe((*p)[i++]) != 0)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

int	close_all_pipes(int **pfx, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		close(pfx[i][0]);
		close(pfx[i][1]);
		i++;
	}
	return (0);
}

int	close_and_dup2(int **pfx, int index, int len, int flag)
{
	if (flag == -1)
	{
		close_all_pipes(pfx, len);
		exit(1);
	}
	if (index == 0 && flag != 1)
		dup2(pfx[0][1], 1);
	else if (index == len - 1)
	{
		if (flag != 2)
			dup2(pfx[index - 1][0], 0);
	}
	else if (index != 0 && index != len - 1)
	{
		if (flag != 2)
			dup2(pfx[index - 1][0], 0);
		if (flag != 1)
			dup2(pfx[index][1], 1);
	}
	close_all_pipes(pfx, len);
	return (0);
}
