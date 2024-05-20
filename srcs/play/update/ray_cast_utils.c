/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:30:38 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 20:27:10 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_radian(double radian)
{
	const double	full_circle = deg2rad(360);

	radian = fmod(radian, full_circle);
	if (radian < 0)
		radian += full_circle;
	return (radian);
}

int	is_ray_facing_south(double angle)
{
	if (0 <= angle && angle < M_PI)
		return (1);
	else
		return (0);
}

int	is_ray_facing_west(double angle)
{
	if (M_PI / 2 <= angle && angle < M_PI * 1.5)
		return (1);
	else
		return (0);
}

static char	get_wall_orientation(t_map *map, int x, int y, t_ray *ray)
{
	if (x == 0)
		return ('E');
	else if (x == (int)map->width)
		return ('W');
	else if (y == 0)
		return ('S');
	else if (y == (int)map->height - 1)
		return ('N');
	if (ray->side == 'H')
	{
		if (map->grid[y - 1][x] != '1' && is_ray_facing_south(ray->angle))
			return ('N');
		else if (map->grid[y + 1][x] != '1' && !is_ray_facing_south(ray->angle))
			return ('S');
	}
	else
	{
		if (map->grid[y][x - 1] != '1' && !is_ray_facing_west(ray->angle))
			return ('W');
		else if (map->grid[y][x + 1] != '1' && is_ray_facing_west(ray->angle))
			return ('E');
	}
	return (0);
}

int	is_wall(t_map *map, double x, double y, t_ray *ray)
{
	ray->x = x;
	ray->y = y;
	if ((int)x < 0 || (int)map->width < (int)x || (int)y < 0
		|| (int)map->height < (int)y)
	{
		ray->size = INT_MAX;
		return (1);
	}
	if ((int)map->height == (int)y)
	{
		ray->obstacle = '1';
		ray->orientation = 'N';
		return (1);
	}
	ray->obstacle = map->grid[(int)y][(int)x];
	if (ray->obstacle == '1')
	{
		ray->orientation = get_wall_orientation(map, (int)x, (int)y, ray);
		return (1);
	}
	return (0);
}
