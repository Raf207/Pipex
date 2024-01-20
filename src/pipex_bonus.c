/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:40:03 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/20 21:54:55 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/include/libft.h"

int	ft_openfile(char *file, int i)
{
	int	fd;

	if (i == 0)
		fd = open(file, O_RDONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_DIRECTORY, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_firstcmd(int pipe[2], char **argv, char **envp)
{
	int	file;

	file = ft_openfile(argv[1], 0);
	dup2(file, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	ft_execution(argv[2], envp);
}

void	ft_lastcmd(int pipe[2], char **argv, char **envp, int argc)
{
	int	file;

	file = ft_openfile(argv[4], 1);
	dup2(file, STDOUT_FILENO);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[1]);
	ft_execution(argv[argc - 2], envp);
}

void	ft_cmdloop(int pipe[2], char **argv, char **envp, int argc)
{
	int	cmd_nb;
	int	id;

	cmd_nb = 3;
	while (cmd_nb < argc - 1)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		if (!id)
		{
			dup2(pipe[1], STDOUT_FILENO);
			close(pipe[0]);
			ft_execution(argv[cmd_nb], envp);
		}
		else
		{
			dup2(pipe[0], STDIN_FILENO);
			close(pipe[1]);
		}
		++cmd_nb;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	p_fd[2];
	int	id;
	int	cmd_nb;
	int	i;

	if (argc < 5)
	{
		ft_putendl_fd("./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	id = fork();
	if (id == -1)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		ft_firstcmd(p_fd, argv, envp);
		ft_cmdloop(p_fd, argv, envp, argc);
	}
	ft_lastcmd(p_fd, argv, envp, argc);
}
