/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:44:30 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/11/12 21:03:55 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"

extern t_alloc	*g_allocs;

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	if (s1[i] == s2[i])
	{
		return (0);
	}
	else
	{
		return (s1[i] - s2[i]);
	}
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0 || (s1[i] == '\0' && s2[i] == '\0'))
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp_n(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n' && str2[i])
	{
		if (str[i] != str2[i])
			return (-1);
		i++;
	}
	if (str[i] == '\n' && str2[i] == '\0')
		return (0);
	return (-1);
}

char	**get_envp(char *env)
{
	char	**envp;

	if (!env)
		return (NULL);
	envp = ft_split(env, ':');
	split_add_to_allocs(envp);
	return (envp);
}

int	_export_out(t_data *data, t_token *token, char *line)
{
	if (token->up == NULL && (ft_strchr(line, 34) || ft_strchr(line, 39)))
	{
		write(2, "minishell: export: `': not a valid identifier\n", 47);
		return (1);
	}
	return (show_env(data, 1));
}
