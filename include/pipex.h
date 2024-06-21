/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:20:23 by rafnasci          #+#    #+#             */
/*   Updated: 2024/06/22 01:21:42 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

int		main(int argc, char **argv, char **envp);
void	ft_secondcmd(int pipe[2], char **argv, char **envp, int fd);
void	ft_firstcmd(int pipe[2], char **argv, char **envp, int fd);
void	ft_execution(char *cmd, char **envp);
void	ft_free(char **tab);
int		ft_openfile(char *file, int i);
int		ft_findpath(char **envp);

#endif