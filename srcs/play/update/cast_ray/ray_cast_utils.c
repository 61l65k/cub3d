/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:30:38 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 13:04:24 by apyykone         ###   ########.fr       */
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

char	get_wall_orientation(t_map *map, int x, int y, t_ray *ray)
{
	if (ray->side == 'H')
	{
		if (is_ray_facing_south(ray->angle) && t_map_get(map, x, y - 1) != '1'
			&& t_map_get(map, x, y - 1) != 'D')
			return ('S');
		else if (!is_ray_facing_south(ray->angle) && t_map_get(map, x, y
				+ 1) != '1' && t_map_get(map, x, y + 1) != 'D')
			return ('N');
	}
	else
	{
		if (is_ray_facing_west(ray->angle) && t_map_get(map, x + 1, y) != '1'
			&& t_map_get(map, x + 1, y) != 'D')
			return ('W');
		else if (!is_ray_facing_west(ray->angle) && t_map_get(map, x - 1,
				y) != '1' && t_map_get(map, x - 1, y) != 'D')
			return ('E');
	}
	return (0);
}

int	is_wall(t_map *map, double x, double y, t_ray *ray)
{
	ray->x = x;
	ray->y = y;
	ray->obstacle = t_map_get_f(map, x, y);
	if (ray->obstacle == '\0')
	{
		ray->distance = INT_MAX;
		return (1);
	}
	if (ray->obstacle == '1' || ray->obstacle == 'D')
	{
		ray->orientation = get_wall_orientation(map, x, y, ray);
		ray->is_door = (ray->obstacle == 'D');
		return (1);
	}
	return (0);
}
