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
#include <sys/types.h>


void update_pwd(t_data *data)
{
	t_lst	*pair;
	char	wd[PATH_MAX];
	
	if (getcwd(wd, PATH_MAX))
		data->pwd = wd;
	pair = new_list("PWD", 4);
	pair->value = new_list(data->pwd, ft_strlen(data->pwd));
	add_val_to_env(pair, data);
}

void update_oldpwd(char *oldpwd, t_data *data)
{
	t_lst *pair;

	pair = new_list("OLDPWD", 7);
	pair->value = new_list(oldpwd, ft_strlen(oldpwd));
	add_val_to_env(pair, data);
}

char *get_cd_path(char *path, t_data *data, t_token *tokens)
{
	char *whole_path;
	if (data->words_count == 1)
		return (path);
	tokens = tokens->up;
	whole_path = ft_strdup2("cd");
	while (tokens)
	{
		if (tokens->location.lenght != 0)
			tokens->location.location[tokens->location.lenght] = 0;
		whole_path = ft_strjoin(whole_path, " ");
		whole_path = ft_strjoin(whole_path, tokens->location.location);
		tokens = tokens->up;
	}
	return (whole_path);
}

int cd(char *path, t_data *data, t_token *tokens)
{
	char *home;
	char oldpwd[PATH_MAX];

	path = get_cd_path(path, data, tokens);
	home = get_home_path(data);
	if (is_empty(path + 2) || is_special(path + 2))
	{
		if (!home || chdir(home) < 0)
			return (cd_error(home, tokens));
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
			return (cd_error(path + 2, tokens));
	}
	if (!getcwd(oldpwd, PATH_MAX))
		return (perror("minishell: cd: "), 1);
	update_path_var(data, oldpwd);
	return (0);
}

int cd_error(char *path, t_token *tokens)
{
	int i;

	(void)(tokens);
	i = 0;
	if (!path)
		return (1);
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
