/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:54:40 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/11/12 21:01:17 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"

extern t_alloc	*g_allocs;

void	signal_ctlc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (g_allocs)
		g_allocs->data->env_lst->status = 130;
}

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	if (g_allocs)
		g_allocs->data->env_lst->status = 0;
}
