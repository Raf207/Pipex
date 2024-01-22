/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:40:52 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/22 13:31:41 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

int		main(int argc, char **argv, char **envp);
void	ft_lastcmd(int pipe[2], char **argv, char **envp, int argc);
void	ft_cmdloop(int pipe[2], char **argv, char **envp, int argc);
void	ft_firstcmd(int pipe[2], char **argv, char **envp);
void	ft_execution(char *cmd, char **envp);
void	ft_free(char **tab);
int		ft_openfile(char *file, int i);
void	ft_errors(int i);

#endif