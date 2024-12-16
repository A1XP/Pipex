/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:35:05 by pkhvorov          #+#    #+#             */
/*   Updated: 2024/12/13 17:43:26 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_var
{
	int	prc;
	int	infile;
	int	outfile;
	int	fd[2];
}	t_var;

void	close_all(t_var *var);
void	dup2_check(int fd1, int fd2);
void	fork_check(t_var *var);
char	*find_cmd(char *cmd, char **env);
void	open_files_pipe(t_var *var, char **argv);
void	execve_cmd(t_var *var, char **argv, char **env, int i);
void	proc(t_var *var, char **argv, char **env, int i);

#endif