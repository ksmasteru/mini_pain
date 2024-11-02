/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:20:13 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/25 00:23:09 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>

int	ft_strlen(char *s1)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	return (i);
}

char	*get_home_path(t_data *data, char *path)
{
	t_lst	*tmp;
	int		found;

	(void)path;
	tmp = data->env_lst;
	found = 0;
	while (tmp)
	{
		if (strcmp(tmp->data, "HOME") == 0)
		{
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (found == 1)
		return (tmp->value->data);
	else
	{
			//print_error("minishell", "cd", NULL, "HOME not set");
		return (NULL);
	}
}

bool	is_special(char *path)
{
	bool	found;
	int		i;

	found = false;
	i = 0;
	while (path[i] && ((path[i] == 32) || (path[i] >= 9 && path[i] <= 13)))
		i++;
	if (path[i] == '~')
	{
		i++;
		found = true;
	}
	while (path[i] && (path[i] == 32 || (path[i] >= 9 && path[i] <= 13)))
		i++;
	if (found && path[i] == 0)
		return (true);
	return (false);
}

int	update_path_var(t_data *data, char *oldpwd)
{
	update_pwd(data);
	update_oldpwd(oldpwd, data);
	return (0);
}
