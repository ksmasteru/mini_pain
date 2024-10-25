/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:20:23 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:21:01 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "sys/wait.h"
# include "tokens.h"
# include <stdio.h>

int		close_and_dup(int **p, int index, int len);
int		execute_cmd(int index, int len, t_data *data, t_token *token);
void	run_cmd(int len, t_data *data);
int		fill_pipes(int ***p, int n);
#endif