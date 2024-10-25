/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:50:07 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/10/13 20:50:26 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"

extern t_alloc	*g_allocs;

void	open_error(char *str)
{
	write(2, "minishell: ", 12);
	ft_putstr_fd(2, str);
	perror(" ");
}

char	*get_file_name(t_token *redirection, t_lst *env_lst, t_data *data)
{
	char	*file_name;

	(void)data;
	(void)env_lst;
	if (redirection->location.location[0] == 0 && redirection->type != 18)
	{
		write(2, "minishell : No such file or directory\n", 39);
		return (NULL);
	}
	file_name = (char *)malloc(sizeof(char) * (redirection->location.lenght
				+ 1));
	alloc_addback(&g_allocs, file_name);
	if (!file_name)
		return (NULL);
	file_name[redirection->location.lenght] = '\0';
	strncpy(file_name, redirection->location.location,
		redirection->location.lenght);
	return (file_name);
}

int	redirect_in_out(char *file_name, char mode)
{
	int	fd;
	int	type;

	type = 0;
	if (mode == 0)
		type = 0;
	else if (mode == 1)
		type = O_RDWR | O_CREAT | O_TRUNC;
	else if (mode == 2)
		type = O_WRONLY | O_APPEND | O_CREAT;
	fd = open(file_name, type, 0644);
	if (fd == -1)
	{
		open_error(file_name);
		return (-1);
	}
	if (mode == 0)
		dup2(fd, 0);
	else
		dup2(fd, 1);
	close(fd);
	if (mode == 0)
		return (0);
	return (1);
}

int	do_redirect(t_token *redirection, t_data *data)
{
	char	*file_name;

	if (redirection == NULL)
		return (1);
	file_name = get_file_name(redirection, data->env_lst, data);
	if (!file_name)
		return (-1);
	if (redirection->type == IN_FILE)
		return (redirect_in_out(file_name, 0));
	else if (redirection->type == OUT_FILE)
		return (redirect_in_out(file_name, 1));
	else if (redirection->type == APPEND_FILE)
		return (redirect_in_out(file_name, 2));
	else if (redirection->type == DELIMETER)
		here_doc(&(redirection->location));
	return (0);
}

int	manage_redirections(t_token *redirection, t_data *data)
{
	t_token	*temp;
	int		flag;

	flag = 0;
	temp = redirection;
	if (!redirection)
		return (0);
	while (temp)
	{
		flag = do_redirect(temp->up, data);
		if (flag == -1)
			break ;
		temp = temp->down;
	}
	return (flag);
}
