/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:40:03 by rafnasci          #+#    #+#             */
/*   Updated: 2024/06/25 20:07:26 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../libft/include/libft.h"

int	ft_findpath(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (i);
	return (-1);
}

int	ft_openfile(char *file, int i)
{
	int	fd;

	if (i == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (i == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_lastcmd(char **argv, char **envp, int argc, int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_execution(argv[argc - 2], envp);
}

void	ft_cmdloop(char **argv, char **envp, int cmd_nb)
{
	int	id;
	int	p_fd[2];

	while (argv[cmd_nb + 2])
	{
		if (pipe(p_fd) == -1)
			exit(EXIT_FAILURE);
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		if (!id)
		{
			close(p_fd[0]);
			dup2(p_fd[1], STDOUT_FILENO);
			close(p_fd[1]);
			ft_execution(argv[cmd_nb], envp);
		}
		else
		{
			close(p_fd[1]);
			dup2(p_fd[0], STDIN_FILENO);
			close(p_fd[0]);
		}
		++cmd_nb;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	p_fd[2];
	int	fd1;

	if (argc < 5)
		ft_errors(0);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			ft_errors(1);
		ft_heredoc(p_fd, argv);
		ft_cmdloop(argv, envp, 3);
		ft_lastcmd(argv, envp, argc, ft_openfile(argv[argc - 1], 2));
	}
	else
	{
		fd1 = ft_openfile(argv[1], 0);
		dup2(fd1, STDIN_FILENO);
		ft_cmdloop(argv, envp, 2);
		ft_lastcmd(argv, envp, argc, ft_openfile(argv[argc - 1], 1));
	}
}
