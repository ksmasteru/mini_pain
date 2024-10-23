NAME = minishell
CC = cc
CFLAGS = -g -fsanitize=address -Wall -Werror -Wextra

SRCS = srcs/minishell.c parsing/tokenization.c parsing/tokens_v2.c execution/run_cmd.c execution/get_paths.c srcs/str_utils.c \
		parsing/ft_split.c execution/get_envp.c execution/cd.c execution/exit.c execution/cd_utils.c  execution/exec_utils.c parsing/tokenization_utils.c\
		 execution/pwd.c execution/exit_utils.c execution/redirections.c parsing/tokens_v3.c execution/print_error.c execution/pipes.c execution/export.c parsing/syntax_error.c \
		srcs/ft_strjoin.c srcs/freeing.c srcs/env_to_list.c srcs/env_utils.c srcs/unset.c parsing/quotes.c srcs/check_builtins.c parsing/new_token.c \
		 parsing/utils.c parsing/expantion.c parsing/expantion_utils.c parsing/quotes_utils.c execution/dispatcher.c  execution/ft_echo.c execution/signals.c  parsing/word_pars_utils.c\

OBJS = $(SRCS:.c=.o)


all : $(NAME)

%.o :	%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -lreadline -o $@

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean