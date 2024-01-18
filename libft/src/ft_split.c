/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:27:58 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/18 12:23:08 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	wordcount;

	wordcount = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			wordcount++;
			while (s[i] != c && s[i])
			{
				i++;
			}
		}
	}
	return (wordcount);
}

static void	ft_free(char **rep)
{
	int	i;

	i = 0;
	while (rep[i] != NULL)
	{
		free(rep[i]);
		i++;
	}
	free(rep);
}

static char	*ft_lettercount(char const *s, char c, char **rep, int word)
{
	int	i;
	int	len;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	rep[word] = ft_calloc(i + 1, sizeof(char));
	if (!rep[word])
	{
		ft_free(rep);
		return (NULL);
	}
	len = 0;
	while (len < i)
	{
		rep[word][len] = s[len];
		len++;
	}
	return (rep[word]);
}

static char	**ft_init(char const *s, char c)
{
	int		wordcount;
	int		i;
	char	**rep;

	wordcount = 0;
	i = 0;
	(rep) = ft_calloc(ft_wordcount(s, c) + 1, sizeof(char *));
	if (!(rep))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			if (!ft_lettercount(&s[i], c, (rep), wordcount))
				return (NULL);
			while (s[i] && s[i] != c)
				i++;
			wordcount++;
		}
	}
	return ((rep));
}

char	**ft_split(char const *s, char c)
{
	char	**rep;

	if (!s)
		return (NULL);
	rep = ft_init(s, c);
	if (!rep)
		return (NULL);
	return (rep);
}

// int	main(void)
// {
// 	char str[] = "je suis une bgssssss";
// 	char c = ' ';
// 	int i = 0;
// 	char **rep;
// 	(void)i;
// 	rep = ft_split(str, c);
// 	// while (rep[i])
// 	// {
// 	// 	printf("%s\n", rep[i]);
// 	// 	i++;
// 	// }
// }