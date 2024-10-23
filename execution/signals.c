/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:54:40 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:54:41 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"

void	signal_ctlc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
		write(STDERR_FILENO, "\n", 1);
}