/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:37:33 by rafnasci          #+#    #+#             */
/*   Updated: 2023/11/24 13:13:07 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cleanlist(t_gnllist **list, char *last)
{
	t_gnllist	*new_node;
	t_gnllist	*temp_node;

	if (!(*list))
		return ;
	while (*list)
	{
		temp_node = (*list)->next;
		free((*list)->content);
		free((*list));
		(*list) = temp_node;
	}
	*list = NULL;
	if (!last)
		return ;
	new_node = malloc (sizeof(t_gnllist));
	if (!new_node)
		return (free(last));
	new_node->next = NULL;
	new_node->content = last;
	*list = new_node;
}

char	*ft_lastpart(t_gnllist *list)
{
	int			i;
	int			len;
	char		*last_part;
	t_gnllist	*last_node;

	last_node = ft_lastnode(list);
	i = 0;
	len = 0;
	last_part = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!last_part)
		return (NULL);
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[++i])
		last_part[len++] = last_node->content[i];
	last_part[len] = '\0';
	if (last_part[0] == '\0')
		return (free(last_part), NULL);
	return (last_part);
}

t_gnllist	*ft_lastnode(t_gnllist *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_addlist(t_gnllist **list, char *str)
{
	t_gnllist	*last_node;
	t_gnllist	*new_node;

	new_node = (t_gnllist *) malloc (sizeof(t_gnllist));
	if (!new_node)
		return (free(str));
	last_node = ft_lastnode(*list);
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = str;
	new_node->next = NULL;
}

int	ft_countlen(t_gnllist *list)
{
	int	tot_len;
	int	i;

	if (!list)
		return (0);
	tot_len = 0;
	while (list)
	{
		i = -1;
		while (list->content[++i])
		{
			tot_len++;
			if (list->content[i] == '\n')
				return (tot_len);
		}
		list = list->next;
	}
	return (tot_len);
}
