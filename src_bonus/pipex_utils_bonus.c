/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:40:01 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/31 12:52:51 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_errors(int i)
{
	if (i == 0)
	{
		ft_putendl_fd("./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	else if (i == 1)
	{
		ft_putendl_fd("./pipex here_doc LIMITER cmd1 cmd2 file", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_execution(char *cmd, char **envp)
{
	char	**split_cmd;
	char	*path_envp;
	char	**all_paths;
	int		i;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path_envp = ft_substr(envp[2], 5, 4654654);
	all_paths = ft_split(path_envp, ':');
	i = -1;
	while (all_paths[++i])
	{
		path = ft_strjoin(ft_strjoin(all_paths[i], "/"), split_cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
			execve(path, split_cmd, envp);
		free(path);
	}
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(split_cmd[0], 2);
	ft_free(split_cmd);
	ft_free(all_paths);
	free(path_envp);
	exit(EXIT_FAILURE);
}

void	ft_heredoc(int pipe[2], char **av)
{
	int		id;

	id = fork();
	if (!id)
		ft_heredoc_input(pipe, av);
	else
	{
		close(pipe[1]);
		dup2(pipe[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	ft_heredoc_input(int pipe[2], char **av)
{
	char	*line;

	close(pipe[0]);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 0);
		line = get_next_line(0);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			exit(EXIT_FAILURE);
		}
		if (write(pipe[1], line, ft_strlen(line)) == -1)
		{
			free(line);
			exit(EXIT_FAILURE);
		}
		if (write(pipe[1], "\n", 1) == -1)
		{
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
	}
}
