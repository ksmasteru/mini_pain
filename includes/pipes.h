#ifndef PIPES_H
#define PIPES_H

#include "tokens.h"
#include "sys/wait.h"
int	close_and_dup(int **p, int index, int len);
int execute_cmd(int index, int len, t_data *data, t_token *token);
void run_cmd(int len, t_data *data);
int	fill_pipes(int ***p, int n);
#endif