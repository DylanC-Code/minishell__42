/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:09:04 by dcastor           #+#    #+#             */
/*   Updated: 2025/05/26 10:35:56 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_words(const char *str, char delimiter)
{
	int				in_word;
	unsigned int	count;
	size_t			i;

	in_word = FALSE;
	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == delimiter)
			in_word = FALSE;
		else if (in_word == FALSE)
		{
			in_word = TRUE;
			count++;
		}
	}
	return (count);
}

static size_t	word_len(char *str, char delimiter)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (str[i] == delimiter)
			return (i);
	return (i);
}

static char	*ft_strndup(char *s, size_t n)
{
	size_t	i;
	char	*res;

	i = -1;
	res = malloc(n + 1);
	if (res == NULL)
		return (NULL);
	while (++i < n)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

static void	free_strs(char **strs)
{
	size_t	i;

	i = -1;
	while (strs && strs[++i])
		free(strs[i]);
	if (strs)
		free(strs);
}

char	**ft_split(char const *s, char c)
{
	const unsigned int	words_nb = count_words(s, c);
	char				*src;
	char				**result;
	size_t				word_index;
	size_t				i;

	src = (char *)s;
	result = malloc(sizeof(char *) * (words_nb + 1));
	if (!result)
		return (NULL);
	word_index = 0;
	i = 0;
	while (src[i])
	{
		while (src[i] == c)
			i++;
		if (!src[i])
			break ;
		result[word_index] = ft_strndup(src + i, word_len(src + i, c));
		if (result[word_index++] == NULL)
			return (free_strs(result), NULL);
		i += word_len(src + i, c);
	}
	result[word_index] = NULL;
	return (result);
}
