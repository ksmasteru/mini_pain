/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:57:47 by aech-chi          #+#    #+#             */
/*   Updated: 2024/08/20 14:12:47 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <sys/types.h>

extern t_alloc	*g_allocs;

int	ft1_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	count_args(char **status)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = 0;
	j = 1;
	while (status[j])
	{
		while (status[j][i])
		{
			i++;
		}
		i = 0;
		n++;
		j++;
	}
	return (n);
}

int	check_argtwo(char *status)
{
	int	i;

	i = 0;
	while (status[i] == ' ' || status[i] == '\t' || status[i] == '+'
		|| status[i] == '-')
		i++;
	while (status[i] > 47 && status[i] < 57)
		i++;
	if (i == (int)ft_strlen(status))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	sign;
	unsigned long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result += str[i] - '0';
		i++;
	}
	return (sign * result);
}

void	split_add_to_allocs(char **status)
{
	int	i;

	i = 0;
	if (!status)
		return ;
	if (!*status)
		return ;
	while (status[i])
		alloc_addback(&g_allocs, status[i++]);
	alloc_addback(&g_allocs, status[i]);
	alloc_addback(&g_allocs, status);
}
