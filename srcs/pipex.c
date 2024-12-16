/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:34 by pkhvorov          #+#    #+#             */
/*   Updated: 2024/12/13 17:46:47 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files_pipe(t_var *var, char **argv)
{
	var->infile = open(argv[1], O_RDONLY);
	if (var->infile < 0)
	{
		perror("Error opening file 1");
		exit(EXIT_FAILURE);
	}
	var->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (var->outfile < 0)
	{
		perror("Error opening file 2");
		exit(EXIT_FAILURE);
	}
	if (pipe(var->fd) == -1)
	{
		perror("Pipe failed");
		close(var->infile);
		close(var->outfile);
		exit(EXIT_FAILURE);
	}
}

void	execve_cmd(t_var *var, char **argv, char **env, int i)
{
	char	**args;
	char	*cmd;

	close_all(var);
	args = ft_split(argv[i], ' ');
	cmd = find_cmd(args[0], env);
	if (!cmd)
	{
		perror("Command 1 not found");
		free(args);
		exit(EXIT_FAILURE);
	}
	execve(cmd, args, env);
	perror("execve failed");
	exit(EXIT_FAILURE);
	waitpid(var->prc, NULL, 0);
}

void	proc(t_var *var, char **argv, char **env, int i)
{
	fork_check(var);
	if (var->prc == 0)
	{
		if (i == 2)
		{
			dup2_check(var->infile, STDIN_FILENO);
			dup2_check(var->fd[1], STDOUT_FILENO);
		}
		else if (i == 3)
		{
			dup2_check(var->fd[0], STDIN_FILENO);
			dup2_check(var->outfile, STDOUT_FILENO);
		}
		execve_cmd(var, argv, env, i);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	int		i;

	if (argc != 5)
	{
		perror("Wrong number of arguments");
		exit(EXIT_FAILURE);
	}
	open_files_pipe(&var, argv);
	i = 2;
	while (i < 4)
	{
		proc(&var, argv, env, i);
		i++;
	}
	close_all(&var);
	return (0);
}
