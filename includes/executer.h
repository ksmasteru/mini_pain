/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:20:05 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:20:09 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parser.h"
# include "tokens.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

char	*ft_strdup2(char *s1);
char	**get_paths(int ac, char ***ultimate, char **envp);
char	*get_path(char **paths, char *cmd);
void	free_it(char ***ultimate, char **paths, int **p, int n);
void	free_it_2(int **p, int n);
int		count_words(char *cmd, char sep);
char	*make_words(char *str, char sep);
char	**ft_split(char *cmd, char sep);
void	free_splited(char ***res, int i);
char	***split_all(int ac, char **av);
char	**get_envp(char **env);
int		ft_strncmp_n(char *str, char *str2);
int		ft_strlen(char *str);
int		ft_putstr_fd(int fd, char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2, char *str);
int		manage_redirections(t_token *redirection, t_data *data);
int		do_redirect(t_token *redirection, t_data *data);
char	*get_file_name(t_token *redirection, t_lst *env_lst, t_data *data);
void	run_multiple_commands(t_data *data);
int		parse_cmd(char *line, char **envp, t_data *data);
void	handle_sigint2(int sig);
void	handle_sigquit(int sig);
void	handle_sigint1(int sig);
int		ft_echo2(t_data *data, char *line, t_token *token);
bool	check_echo_n(t_token **tmp);
int		set_exec_args(t_token *token, t_data *data, char ***args, char **cmd);
void	free_exec_args(char **args, char *cmd, t_tree *head);
void	free_data_variables(t_data *data, int flag);
void	free_all_tokens(t_token **tokens);
void	free_ls_2(t_token *token, int direction);
char	*get_home_path(t_data *data);
int		ft_exit(t_data *data, char *line, t_token *token);
void	exit_empty(int status);
int		check_argtwo(char *status);
int		count_args(char **status);
int		cd(char *path, t_data *data, t_token *tokens);
int		ft_atoi(const char *str);
int		pwd(char *cmd, t_token *tokens, t_data *data);
int		unset(t_data *data, t_token *token, char *line);
int		check_builtin_multiple(char *line, t_data *data, t_token *token, int n);
int		built_in_code(char *line);
bool	not_valid_variable(t_token *token);
int		unset_error(t_token *token);
void	ft_lstdelete(t_lst **head, t_lst *to_delete);
int		print_error_errno(char *s1, char *s2, char *s3);
int		print_error(char *s1, char *s2, char *s3, char *message);
void	update_pwd(t_data *data);
void	update_oldpwd(char *oldpwd, t_data *data);
void	_free(void **add);
int		check_balanced_quotes(char *str);
void	alloc_addback(t_alloc **head, void *add);
void	free_allocs(t_alloc **allocs);
void	split_add_to_allocs(char **status);
bool	is_special(char *path);
int		cd_error(char *path, t_token *tokens);
int		write_exit_code(char **status);
int		built_in_code(char *line);
int		swap_if_key(t_lst **head, t_lst *pair);
void	ft_putstr(int fd, char *str);
int		close_and_dup2(int **pfx, int index, int len, int flag);
int		init_exec_check(t_token *head, t_data *data, int index);
void	free_tlst(t_lst **node);
void	signal_ctlc_heredoc(int sig);
int		set_up_heredoc(char **str);
void	here_doc(t_slice *slice);
int		check_builtin(char *line, t_data *data);
int		_export_out(t_data *data, t_token *token, char *line);
bool	is_numeric(t_token *token);
char	*get_cd_path(char *path, t_data *data, t_token *tokens);
void	open_error(char *str);
int		update_path_var(t_data *data);
int		show_export(t_data *data);
void	set_off_heredoc(int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	signal_ctlc_heredoc(int sig);
void	signal_ctlc(int sig);
void	restore_tty(int flag);
int		is_builtin(char *line);
char	*read_cmd(void);
int		ft_isalpha(int c);
int		init_check_main_cmd(t_data *data, t_token *token);
void	print_cmd_nfound(char *cmd);
#endif