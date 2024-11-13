/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:47:47 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:47:49 by hes-saqu         ###   ########.fr       */
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

int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(2, s1);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, s2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, s3);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, message);
	}
	write(2, "\n", 1);
	return (-1);
}

int	print_error_errno(char *s1, char *s2, char *s3)
{
	print_error(s1, s2, s3, strerror(errno));
	errno = 0;
	return (-1);
}

void	print_cmd_nfound(char *cmd)
{
	if (cmd && cmd[0] != 0)
	{
		ft_putstr_fd(2, "minishell: ");
		ft_putstr_fd(2, cmd);
		ft_putstr_fd(2, ": command not found\n");
	}
}
