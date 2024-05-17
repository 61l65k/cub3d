/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:55:04 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/17 14:24:24 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	const double	full_circle = 2 * M_PI;

	angle = fmod(angle, full_circle);
	if (angle < 0)
		angle += full_circle;
	return (angle);
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	get_hrzn_intersection(t_ray *ray, t_map *map, t_player *player)
{
	double y_intercept, x_intercept;
	double y_step, x_step;
	double next_horz_x, next_horz_y;
	int map_x, map_y;
	y_intercept = floor(player->y / GRID_UNIT_SCALE) * GRID_UNIT_SCALE;
	y_intercept += (ray->angle > 0 && ray->angle < M_PI) ? GRID_UNIT_SCALE : 0;
	x_intercept = player->x + (y_intercept - player->y) / tan(ray->angle);
	y_step = GRID_UNIT_SCALE;
	y_step *= (ray->angle > 0 && ray->angle < M_PI) ? 1 : -1;
	x_step = y_step / tan(ray->angle);
	next_horz_x = x_intercept;
	next_horz_y = y_intercept;
	while (next_horz_x >= 0 && next_horz_x < map->width * GRID_UNIT_SCALE
		&& next_horz_y >= 0 && next_horz_y < map->height * GRID_UNIT_SCALE)
	{
		map_x = floor(next_horz_x / GRID_UNIT_SCALE);
		map_y = floor(next_horz_y / GRID_UNIT_SCALE) - ((ray->angle > 0
					&& ray->angle < M_PI) ? 0 : 1);
		if (map_x >= 0 && map_x < (int)map->width && map_y >= 0
			&& map_y < (int)map->height)
		{
			if (map->grid[map_y][map_x] == '1')
			{
				ray->x = next_horz_x;
				ray->y = next_horz_y;
				ray->size = distance(player->x, player->y, next_horz_x,
						next_horz_y);
				return ;
			}
		}
		else
		{
			break ;
		}
		next_horz_x += x_step;
		next_horz_y += y_step;
	}
	ray->size = INFINITY;
}

void	get_vrtl_intersection(t_ray *ray, t_map *map, t_player *player)
{
	int	map_x;
	int	map_y;

	double x_intercept, y_intercept;
	double x_step, y_step;
	double next_vert_x, next_vert_y;
	x_intercept = floor(player->x / GRID_UNIT_SCALE) * GRID_UNIT_SCALE;
	x_intercept += (ray->angle < M_PI_2 || ray->angle > 3
			* M_PI_2) ? GRID_UNIT_SCALE : 0;
	y_intercept = player->y + (x_intercept - player->x) * tan(ray->angle);
	x_step = GRID_UNIT_SCALE;
	x_step *= (ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2) ? 1 : -1;
	y_step = x_step * tan(ray->angle);
	next_vert_x = x_intercept;
	next_vert_y = y_intercept;
	while (next_vert_x >= 0 && next_vert_x < map->width * GRID_UNIT_SCALE
		&& next_vert_y >= 0 && next_vert_y < map->height * GRID_UNIT_SCALE)
	{
		map_x = floor(next_vert_x / GRID_UNIT_SCALE) - ((ray->angle < M_PI_2
					|| ray->angle > 3 * M_PI_2) ? 0 : 1);
		map_y = floor(next_vert_y / GRID_UNIT_SCALE);
		if (map->grid[map_y][map_x] == '1')
		{
			ray->x = next_vert_x;
			ray->y = next_vert_y;
			ray->size = distance(player->x, player->y, next_vert_x,
					next_vert_y);
			return ;
		}
		next_vert_x += x_step;
		next_vert_y += y_step;
	}
	ray->size = INFINITY;
}

void	cast_ray(t_ray *ray, t_map *map, t_player *player)
{
	t_ray	hrzn_intersection;
	t_ray	vrtl_intersection;

	printf("CAST RAY\n");
	hrzn_intersection = (t_ray){0};
	vrtl_intersection = (t_ray){0};
	// double delta_dist_x, delta_dist_y;
	// double next_horz_x, next_horz_y;
	// double next_vert_x, next_vert_y;
	hrzn_intersection.angle = normalize_angle(ray->angle);
	vrtl_intersection.angle = normalize_angle(ray->angle);
	hrzn_intersection.side = 'H';
	vrtl_intersection.side = 'V';
	get_hrzn_intersection(&hrzn_intersection, map, player);
	get_vrtl_intersection(&vrtl_intersection, map, player);
	if (hrzn_intersection.size <= vrtl_intersection.size)
		*ray = hrzn_intersection;
	else
		*ray = vrtl_intersection;
}
