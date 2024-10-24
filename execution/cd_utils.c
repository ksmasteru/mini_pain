/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:20:13 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:20:15 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <dirent.h>
#include <sys/types.h>
#include <limits.h>

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

char	*get_home_path(t_data *data)
{
	t_lst	*tmp;
	int	found;

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
		print_error("minishell", "cd", NULL, "HOME not set");
		return (NULL);
	}
}

bool	is_special(char *path)
{
	int	i;
	bool	found;

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

int	update_path_var(t_data *data)
{
	char	oldpwd[PATH_MAX];

	if (!getcwd(oldpwd, PATH_MAX))
		return (perror("minishell: cd: "), 1);
	update_pwd(data);
	update_oldpwd(oldpwd, data);
	return (0);
}
