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
#include <limits.h>

void	handle_error(t_data *data)
{
	if (!data->pwd)
	{
		perror("getcwd: ");
		return ;
	}
	printf("%s\n", data->pwd);
}


int	pwd(char *cmd, t_token *tokens, t_data *data)
{
	char	wd[PATH_MAX];

	if (!getcwd(wd, PATH_MAX))
		return (handle_error(data), 0);
	printf("%s\n", wd);
	return (0);
}
