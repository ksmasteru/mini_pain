/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:39:40 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:39:47 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"

void	ft_echo(t_token *tmp, bool n)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	if (tmp->location.location[0] != 0)
		tmp->location.location[tmp->location.lenght] = 0;
	while (i < ft_strlen(tmp->location.location))
	{
		write(1, tmp->location.location + i, 1);
		i++;
	}
	if (tmp->location.location[0] != 0 && tmp->up
		&& tmp->up->location.location[0] != 0)
		write(1, " ", 1);
	if (!n && !tmp->up)
		write(1, "\n", 1);
}

void	restore_tty(int flag)
{
	int	fd;

	if (flag == 0)
	{
		close(0);
		fd = open("/dev/tty", O_RDONLY);
		if (fd == -1)
			perror("open");
	}
	else
	{
		close(1);
		fd = open("/dev/tty", O_WRONLY);
		if (fd == -1)
			perror("open");
	}
}

int	ft_echo2(t_data *data, char *line, t_token *token)
{
	t_token	*tmp;
	bool	n;

	(void)line;
	tmp = token->up;
	if (data->flag == -1)
		return (1);
	if (tmp)
	{
		n = check_echo_n(&tmp);
		while (tmp)
		{
			ft_echo(tmp, n);
			tmp = tmp->up;
		}
	}
	else
		write (1, "\n", 1);
	return (0);
}

bool	check_echo_n(t_token **tmp)
{
	size_t	i;
	bool	value;

	value = false;
	if (!(*tmp))
		return (false);
	while (*tmp)
	{
		i = 1;
		if ((*tmp)->location.lenght >= 2 && (*tmp)->location.location[0] == '-')
		{
			while (i < (*tmp)->location.lenght)
			{
				if ((*tmp)->location.location[i++] != 'n')
					return (value);
			}
			value = true;
		}
		else
			return (value);
		*tmp = (*tmp)->up;
	}
	return (value);
}
