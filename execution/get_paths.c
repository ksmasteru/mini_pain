/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:46:17 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:46:18 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"

extern t_alloc *g_allocs;

char **get_paths(int ac, char ***ultimate, char **envp)
{
	int i;
	char **res;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (ac + 1));
	alloc_addback(&g_allocs, res);
	if (!res)
		return (NULL);
	while (i < ac)
	{
		res[i] = get_path(envp, ultimate[i][0]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char *get_path(char **paths, char *cmd)
{
	int i;
	char *cmd_path;
	char *path_jnd;

	i = 0;
	if (built_in_code(cmd) != 0)
		return (ft_strdup2(cmd));
	if (access(cmd, X_OK | F_OK) == 0)
		return (ft_strdup2(cmd));
	while (paths[i] != NULL && cmd[0] && cmd[0] != '/' && cmd[0] != '.')
	{
		path_jnd = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path_jnd, cmd);
		if (access(cmd_path, X_OK | F_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (ft_strdup2(cmd));
}
