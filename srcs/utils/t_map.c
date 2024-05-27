/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:18:26 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/27 14:14:56 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include <stdio.h>

int	t_map_insert(t_map *t_map, int x, int y, char new_value)
{
	if (x < 0 || y < 0 || x >= (int)t_map->width || y >= (int)t_map->height)
		return (-1);
	t_map->grid[y][x] = new_value;
	return (0);
}

char	t_map_get(const t_map *t_map, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)t_map->width || y >= (int)t_map->height)
		return ('\0');
	if (!t_map->grid[y][x])
		return (' ');
	return (t_map->grid[y][x]);
}

void	t_map_print(const t_map *t_map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < t_map->height)
	{
		x = 0;
		while (x < t_map->width)
		{
			printf("%c", t_map_get(t_map, x, y));
			x++;
		}
		printf("\n");
		y++;
	}
}
