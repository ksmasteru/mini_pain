/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:20:13 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:20:14 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define ALLOC 'A'
# define FREE 'F'

/* The Struct used in the garbage collector */
typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}					t_gc;

typedef struct s_lst
{
	int				status;
	char			*data;
	struct s_lst	*next;
	struct s_lst	*value;
}					t_lst;

#endif /*	MINISHELL_H	*/
