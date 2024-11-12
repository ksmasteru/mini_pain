/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:32:15 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/11/12 21:03:33 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

extern t_alloc	*g_allocs;

bool	is_numeric(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	if (token->location.location[0] != 0)
		token->location.location[token->location.lenght] = 0;
	str = token->location.location;
	if (str[0] == 0)
	{
		print_error("minishell ", "exit", str, "numeric argument required");
		return (false);
	}
	else if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
	while (i < ft_strlen(str))
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			print_error("minishell ", "exit", str, "numeric argument required");
			return (false);
		}
	}
	return (true);
}

int	ft_exit(t_data *data, char *line, t_token *token)
{
	int	code;

	(void)line;
	code = data->env_lst->status;
	if (data->words_count == 1)
		write(2, "exit\n", 5);
	if (token->up && !is_numeric(token->up))
		code = 255;
	else if (token->up && !token->up->up)
	{
		if (token->up->location.location[0] != 0)
			token->up->location.location[token->up->location.lenght] = 0;
		code = ft_atoi(token->up->location.location);
	}
	else if (token->up && token->up->up)
	{
		print_error("minishell ", "exit", NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	free_data_variables(data, 1);
	exit(code);
}

void	exit_empty(int status)
{
	write(2, "exit\n", 6);
	exit(status);
}
