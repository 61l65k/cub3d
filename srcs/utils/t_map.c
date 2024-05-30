/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:18:26 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/30 17:52:34 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include <math.h>

int	t_map_insert(t_map *t_map, int x, int y, char new_value)
{
	if (x < 0 || y < 0 || x >= (int)t_map->width || y >= (int)t_map->height)
		return (-1);
	t_map->grid[y][x] = new_value;
	return (0);
}

int	t_map_insert_f(t_map *t_map, double x, double y, char new_value)
{
	if (x < 0 || y < 0 || x >= (int)t_map->width || y >= (int)t_map->height)
		return (-1);
	t_map->grid[(int)y][(int)x] = new_value;
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

char	t_map_get_f(const t_map *t_map, double x, double y)
{
	if (x < 0 || y < 0 || x >= (int)t_map->width || y >= (int)t_map->height)
		return ('\0');
	if (!t_map->grid[(int)y][(int)x])
		return (' ');
	return (t_map->grid[(int)y][(int)x]);
}

t_coords	t_map_get_collision_checked_coords(const t_map *t_map,
	t_coords new, t_coords old)
{
	char		map_char;

	new.x = fmin(fmax(new.x, 0.01), t_map->width - 0.01);
	new.y = fmin(fmax(new.y, 0.01), t_map->height - 0.01);
	map_char = t_map_get_f(t_map, new.x, new.y);
	if (map_char != '1')
		return (new);
	map_char = t_map_get_f(t_map, old.x, new.y);
	if (map_char != '1')
	{
		new.x = old.x;
		return (new);
	}
	map_char = t_map_get_f(t_map, new.x, old.y);
	if (map_char != '1')
	{
		new.y = old.y;
		return (new);
	}
	return (old);
}
