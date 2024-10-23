/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:47:00 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:47:36 by hes-saqu         ###   ########.fr       */
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

extern t_alloc *g_allocs;
int fill_pipes(int ***p, int n)
{
	int i;

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

int close_all_pipes(int **pfx, int len)
{
	int i;

	i = 0;
	while (i < len - 1)
	{
		close(pfx[i][0]);
		close(pfx[i][1]);
		i++;
	}
	return (0);
}

int close_and_dup2(int **pfx, int index, int len, int flag)
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

int set_up_heredoc(char **str)
{
	int fd;

	signal(SIGINT, signal_ctlc_heredoc);
	if (access("/tmp/.tmp.txt", F_OK) == 0)
		unlink("/tmp/.tmp.txt");
	*str = ft_strdup2("PGD12..fD");
	fd = open("/tmp/.tmp.txt", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		perror("open");
	return (fd);
}

void set_off_heredoc(int fd)
{
	close(fd);
	fd = open("/tmp/.tmp.txt", O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		perror("open");
	dup2(fd, 0);
	close(fd);
}

void here_doc(t_slice *slice)
{
	int fd;
	char *read_str;
	
	restore_tty(0);
	fd = set_up_heredoc(&read_str);
	signal(SIGINT, signal_ctlc_heredoc);
	if (fd == -1)
		return;
	if (slice->location[0] != 0)
		slice->location[slice->lenght] = '\0';
	while (read_str && strcmp(read_str, slice->location))
	{
		read_str = readline("> ");
		if (!read_str)
			break;
		alloc_addback(&g_allocs, read_str);
		if (strcmp(read_str, slice->location) != 0)
		{
			write(fd, read_str, ft_strlen(read_str));
			write(fd, "\n", 2);
		}
	}
	set_off_heredoc(fd);
}
