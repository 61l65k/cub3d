/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:33:06 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/30 15:56:21 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, const char *charset);
static int	split_words(char const *s, const char *charset, char **result);

char	**ft_splits(char const *s, const char *charset)
{
	char	**result;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, charset);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (result == NULL)
		return (NULL);
	if (!split_words(s, charset, result))
	{
		free(result);
		result = NULL;
		return (NULL);
	}
	result[word_count] = NULL;
	return (result);
}

static int	count_words(char const *s, const char *charset)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (ft_strchr(charset, *s))
			s++;
		if (*s)
			word_count++;
		while (*s && ft_strchr(charset, *s) == NULL)
			s++;
	}
	return (word_count);
}

static int	split_words(char const *s, const char *charset, char **result)
{
	int			i;
	char const	*start_of_word;

	i = 0;
	while (*s)
	{
		while (ft_strchr(charset, *s))
			s++;
		if (*s)
		{
			start_of_word = s;
			while (*s && ft_strchr(charset, *s) == NULL)
				s++;
			result[i] = ft_substr(start_of_word, 0, s - start_of_word);
			if (result[i] == NULL)
			{
				while (--i >= 0)
					free(result[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}
