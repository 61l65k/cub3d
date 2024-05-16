/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:53:26 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 13:21:43 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define INIT_CAPACITY 80

static size_t	line_realloc(char **line, size_t old_cap)
{
	char	*new_line;
	size_t	i;
	size_t	new_cap;

	new_cap = old_cap + INIT_CAPACITY;
	new_line = NULL;
	if (new_cap > old_cap)
		new_line = malloc(new_cap);
	if (!new_line)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	i = 0;
	while (i < old_cap)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	free(*line);
	*line = new_line;
	return (new_cap);
}

/*
 *	returns 1 on newline,
 *	0 on EOF,  -1 on error.
 */
int	gnl(int fd, char **line)
{
	size_t	i;
	size_t	cap;

	if (read(fd, 0, 0) == -1)
		return (-1);
	cap = INIT_CAPACITY;
	*line = malloc(cap);
	i = 0;
	while (*line && read(fd, &(*line)[i], 1))
	{
		if ((*line)[i] == '\n')
		{
			(*line)[i] = '\0';
			return (1);
		}
		if (++i >= cap)
			cap = line_realloc(line, cap);
	}
	if (!*(line))
		return (-1);
	(*line)[i] = '\0';
	return (0);
}
