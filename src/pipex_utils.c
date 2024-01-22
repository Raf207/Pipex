/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:13:57 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/22 12:06:42 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/include/libft.h"

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
