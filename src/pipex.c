/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:01:28 by rafnasci          #+#    #+#             */
/*   Updated: 2024/06/25 20:06:02 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_openfile(char *file, int i)
{
	int	fd;

	if (i == 0)
		fd = open(file, O_RDONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_firstcmd(int pipe[2], char **argv, char **envp, int fd)
{
	dup2(fd, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(fd);
	ft_execution(argv[2], envp);
}

void	ft_secondcmd(int pipe[2], char **argv, char **envp, int fd)
{
	dup2(fd, STDOUT_FILENO);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[1]);
	close(pipe[0]);
	close(fd);
	ft_execution(argv[3], envp);
}

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int	p_fd[2];
	int	id;
	int	id2;

	if (argc != 5)
		ft_error("./pipex file1 cmd1 cmd2 file2");
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	id = fork();
	if (id == -1)
		exit(EXIT_FAILURE);
	if (id == 0)
		ft_firstcmd(p_fd, argv, envp, ft_openfile(argv[1], 0));
	id2 = fork();
	if (id2 == -1)
		exit(EXIT_FAILURE);
	if (id2 == 0)
		ft_secondcmd(p_fd, argv, envp, ft_openfile(argv[4], 1));
	close(p_fd[0]);
	close(p_fd[1]);
	while (!waitpid(id, NULL, 0) || !waitpid(id2, NULL, 0))
		;
	return (0);
}
