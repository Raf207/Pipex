/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:40:52 by rafnasci          #+#    #+#             */
/*   Updated: 2024/06/22 01:21:33 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

int		main(int argc, char **argv, char **envp);
void	ft_lastcmd(char **argv, char **envp, int argc, int fd);
void	ft_cmdloop(char **argv, char **envp, int argc);
void	ft_execution(char *cmd, char **envp);
void	ft_free(char **tab);
int		ft_openfile(char *file, int i);
void	ft_errors(int i);
void	ft_heredoc(int pipe[2], char **av);
void	ft_heredoc_input(int pipe[2], char **av);
int		ft_findpath(char **envp);

#endif