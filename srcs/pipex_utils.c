/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:39:48 by pkhvorov          #+#    #+#             */
/*   Updated: 2024/12/13 17:41:34 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(t_var *var)
{
	close(var->fd[0]);
	close(var->fd[1]);
	close(var->infile);
	close(var->outfile);
}

void	dup2_check(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
}

void	fork_check(t_var *var)
{
	var->prc = fork();
	if (var->prc == -1)
	{
		perror("fork failed");
		close(var->infile);
		close(var->outfile);
		exit(EXIT_FAILURE);
	}
}

static char	*find_path(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char *cmd, char **env)
{
	char	*path_env;
	char	**bin_paths;
	char	*tmp;
	int		i;

	path_env = find_path(env);
	if (path_env == NULL)
		return (NULL);
	bin_paths = ft_split(path_env, ':');
	if (bin_paths == NULL)
		return (NULL);
	i = 0;
	while (bin_paths[i] != NULL)
	{
		tmp = ft_strjoin(bin_paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (tmp == NULL)
			return (NULL);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}
