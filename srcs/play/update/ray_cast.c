/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:48:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/18 02:55:26 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(t_ray *ray, t_map *map, t_player *player)
{
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;

	map_x = (int)player->x;
	map_y = (int)player->y;
	delta_dist_x = fabs(1 / cos(ray->angle));
	delta_dist_y = fabs(1 / sin(ray->angle));
	if (cos(ray->angle) < 0)
	{
		step_x = -1;
		side_dist_x = (player->x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
	}
	if (sin(ray->angle) < 0)
	{
		step_y = -1;
		side_dist_y = (player->y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_y >= 0 && map_y < (int)map->height && map_x >= 0
			&& map_x < (int)map->width)
		{
			if (map->grid[map_y][map_x] == '1')
				hit = 1;
		}
		else
		{
			hit = 1;
		}
	}
	if (side == 0)
	{
		ray->size = (map_x - player->x + (1 - step_x) / 2) / cos(ray->angle);
		ray->orientation = (step_x == -1) ? 'W' : 'E';
	}
	else
	{
		ray->size = (map_y - player->y + (1 - step_y) / 2) / sin(ray->angle);
		ray->orientation = (step_y == -1) ? 'N' : 'S';
	}
	ray->x = player->x + ray->size * cos(ray->angle);
	ray->y = player->y + ray->size * sin(ray->angle);
	ray->side = (side == 0) ? 'H' : 'V';
}
