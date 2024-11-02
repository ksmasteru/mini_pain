/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:21:40 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:21:41 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/tokens.h"
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>

void	update_pwd(t_data *data)
{
	t_lst	*pair;
	char	wd[PATH_MAX];

	if (getcwd(wd, PATH_MAX))
		data->pwd = wd;
	pair = new_list("PWD", 4);
	pair->value = new_list(data->pwd, ft_strlen(data->pwd));
	add_val_to_env(pair, data);
}

void	update_oldpwd(char *oldpwd, t_data *data)
{
	t_lst	*pair;

	pair = new_list("OLDPWD", 7);
	pair->value = new_list(oldpwd, ft_strlen(oldpwd));
	add_val_to_env(pair, data);
}

char	*get_cd_path(t_token *tokens)
{
	char	*whole_path;

	whole_path = NULL;
	if (!tokens->up || tokens->up->location.location[0] == 0)
		return (NULL);
	tokens = tokens->up;
	while (tokens)
	{
		if (tokens->location.lenght != 0)
			tokens->location.location[tokens->location.lenght] = 0;
		if (whole_path && tokens->location.location[0] != 0)
			whole_path = ft_strjoin(whole_path, " ");
		whole_path = ft_strjoin(whole_path, tokens->location.location);
		tokens = tokens->up;
	}
	return (whole_path);
}

int	cd(char *path, t_data *data, t_token *tokens)
{
	char	*home;
	char	oldpwd[PATH_MAX];

	if (getcwd(oldpwd, PATH_MAX))
		data->oldpwd = oldpwd;
	if (get_cd_paths(data, tokens, &path, &home) != 0)
		return (1);
	if (!path || is_empty(path) || is_special(path))
	{
		if (!home || chdir(home) < 0)
			return (cd_error(home, path, tokens));
	}
	else
	{
		if (tokens->up && tokens->up->up)
		{
			write(2, "cd: too many arguments\n", 24);
			return (1);
		}
		if (tokens->up->location.location[0] != 0)
			tokens->up->location.location[tokens->up->location.lenght] = 0;
		if (chdir(tokens->up->location.location) < 0)
			return (cd_error(home, path, tokens));
	}
	return (update_path_var(data, oldpwd));
}

int	cd_error(char *home, char *path, t_token *tokens)
{
	int	i;

	(void)(tokens);
	i = 0;
	if (!path)
	{
		if (!home)
			print_error("minishell", "cd", NULL, "HOME not set");
		return (1);
	}
	write(2, "cd: ", 5);
	while (path[i])
	{
		write(2, &path[i], 1);
		i++;
	}
	write(2, ": ", 2);
	perror("");
	return (1);
}
