/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:49:19 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:49:21 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <dirent.h>
#include <sys/types.h>

int	_getcwd(char *a, size_t b)
{
	char	*wd;

	(void)b;
	(void)a;
	wd = getcwd(0, 0);
	printf("%s\n", wd);
	if (wd)
		free(wd);
	return (0);
}

int	pwd(char *cmd, t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens->up)
	{
		write(2, "pwd:	too many arguments\n", 25);
		return (1);
	}
	while (cmd[i])
	{
		if (cmd[i] == '-')
		{
			printf("pwd: ");
			while (cmd[i] != '\0' && cmd[i] != '\n' && cmd[i] != '\t'
				&& cmd[i] != ' ')
			{
				printf("%c", cmd[i]);
				i++;
			}
			printf(": invalid option\n");
			return (1);
		}
		i++;
	}
	return (_getcwd(0, 0));
}
