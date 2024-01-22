/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:40:01 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/22 16:43:17 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/include/libft.h"

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
	path_envp = ft_substr(envp[4], 5, 4654654);
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

void	ft_heredoc(int pipe[2], char **av, char **env, int ac)
{
	int		file;
	char	*line;

	file = ft_openfile(av[1], 0);
	line = get_next_line(file);
	close(pipe[0]);
	while (line && !ft_strstr(line, av[2]))
	{
		if (write(pipe[1], line, ft_strlen(line)) == -1)
		{
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(file);
	}
	if (line && ft_strstr(line, av[2]))
	{
		if (write(pipe[1], line, ft_strlen(line)
				- ft_strlen(ft_strstr(line, av[2]))) == -1)
		{
			free(line);
			exit(EXIT_FAILURE);
		}
	}
}
