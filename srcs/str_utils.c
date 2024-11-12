/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:31:02 by aech-chi          #+#    #+#             */
/*   Updated: 2024/11/12 21:07:36 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "sys/wait.h"
#include <stdbool.h>

extern t_alloc	*g_allocs;

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	char_c;

	i = 0;
	char_c = (char)c;
	while (s[i])
	{
		if (s[i] == char_c)
			return ((char *)&s[i]);
		i++;
	}
	if (char_c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, str + i, 1);
		i++;
	}
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	if (line[0] == 0)
		return (true);
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == 0 || line[i] == '\n')
		return (true);
	return (false);
}

char	*read_cmd(void)
{
	char	*line;

	while (1)
	{
		line = readline("\e[0;32m[minishell]$ \e[0;0m");
		if (!line)
			return (NULL);
		else if (is_empty(line))
		{
			free(line);
			continue ;
		}
		else
			break ;
	}
	if (access(".tmp.txt", F_OK) == 0)
		unlink(".tmp.txt");
	add_history(line);
	alloc_addback(&g_allocs, line);
	return (line);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
