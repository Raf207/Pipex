/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:30:20 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/11 21:02:12 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int	*ft_findpath(int pipe[2], char *prog, char **envp)
{
	char	*args[4];
	int		p_id;

	p_id = fork();
	if (p_id == 0)
	{
		args[0] = "/usr/bin/whereis";
		args[1] = "whereis";
		args[2] = prog;
		args[3] = NULL;
		close(pipe[0]);
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
		execve(args[0], args + 1, envp);
		return (1);
	}
	return (0);
}

int	ft_firstchild(int pipe1[2], int pipe2[2], char **envp, char *cmd)
{
	char	path[100];
	char	**split_cmd;

	split_cmd = ft_split(cmd, " ");
	ft_findpath(pipe2, split_cmd[0], envp);
	close(pipe2[1]);
	close(pipe1[0]);
	read(pipe2[0], &path, sizeof(path) - 1);
	close(pipe2[0]);
	dup2(pipe1[1], STDOUT_FILENO);
	close(pipe1[1]);
	execve(path, split_cmd, envp);
	return (1);
}

int	ft_secondchild(int pipe1[2], int pipe2[2], char **envp, char **argv)
{
	char	path[100];
	char	**split_cmd;
	int		file;

	file = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	split_cmd = ft_split(argv[3], " ");
	ft_findpath(pipe2, split_cmd[0], envp);
	close(pipe2[1]);
	close(pipe1[0]);
	read(pipe2[0], &path, sizeof(path) - 1);
	close(pipe2[0]);
	dup2(pipe1[1], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(pipe1[1]);
	close(file);
	execve(path, split_cmd, envp);
	return (1);
}


int	main(int argc, char **argv, char **envp)
{
	int	p_fd[2];
	int	p_fd2[2];
	int	id;
	int	id2;
	int	file;

	if (pipe(p_fd) == -1 || pipe(p_fd2) == -1)
	{
		perror("pipe");
		return (1);
	}
	id = fork();
	if (id == 0)
		ft_firstchild(p_fd, p_fd2, envp, argv[1]);
	id2 = fork();
	if (id2 == 0)
		ft_firstchild(p_fd, p_fd2, envp, argv);
	close(file);
	close(p_fd[0]);
	close(p_fd[1]);
	close(p_fd2[0]);
	close(p_fd2[1]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}

