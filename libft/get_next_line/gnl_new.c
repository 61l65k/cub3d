/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:53:26 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/02 00:15:36 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MAX_LINE 200000

/*
 *	returns 1 on newline,
 *	0 on EOF,  -1 on error.
 */

int	gnl(int fd, char **line)
{
	char	buf;
	int		i;

	if (read(fd, 0, 0) == -1)
		return (-1);
	*line = malloc(MAX_LINE);
	if (!*(line))
		return (-1);
	i = 0;
	while (read(fd, &buf, 1))
	{
		if (buf == '\n')
		{
			(*line)[i] = '\0';
			return (1);
		}
		(*line)[i++] = buf;
	}
	(*line)[i] = '\0';
	return (0);
}
