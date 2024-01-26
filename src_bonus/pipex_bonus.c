/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:40:03 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/26 16:58:30 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../libft/include/libft.h"

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

	file = ft_openfile(argv[argc - 1], 1);
	dup2(file, STDOUT_FILENO);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[1]);
	ft_execution(argv[argc - 2], envp);
}

void	ft_cmdloop(int pipe[2], char **argv, char **envp, int cmd_nb)
{
	int	id;

	while (argv[cmd_nb + 2])
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

	if (argc < 5)
		ft_errors(0);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			ft_errors(1);
		ft_heredoc(p_fd, argv);
		ft_cmdloop(p_fd, argv, envp, 3);
	}
	else
	{
		dup2(ft_openfile(argv[1], 0), STDIN_FILENO);
		ft_cmdloop(p_fd, argv, envp, 2);
	}
	ft_lastcmd(p_fd, argv, envp, argc);
}
