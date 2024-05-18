/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:48:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/18 19:33:15 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_radian(double radian)
{
	double	full_circle;

	full_circle = deg2rad(360);
	radian = fmod(radian, full_circle);
	if (radian < 0)
		radian += full_circle;
	return (radian);
}

int	is_south(double angle)
{
	if (0 <= angle && angle < M_PI)
		return (1);
	else
		return (0);
}

int	is_west(double angle)
{
	if (M_PI / 2 <= angle && angle < M_PI * 1.5)
		return (1);
	else
		return (0);
}

char	get_wall_orientation(t_map *map, int x, int y, t_ray *ray)
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
		if (map->grid[y - 1][x] != '1' && is_south(ray->angle))
			return ('N');
		else if (map->grid[y + 1][x] != '1' && !is_south(ray->angle))
			return ('S');
	}
	else
	{
		if (map->grid[y][x - 1] != '1' && !is_west(ray->angle))
			return ('W');
		else if (map->grid[y][x + 1] != '1' && is_west(ray->angle))
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

void	get_hrzn_intersection(t_ray *ray, t_map *map, t_player *player)
{
	const int	is_south_direction = is_south(ray->angle);

	double a_x, a_y, x_step, y_step, ray_section;
	ray->size = 0;
	if (ray->angle == deg2rad(180) || ray->angle == deg2rad(360))
	{
		ray->size = INT_MAX;
		return ;
	}
	if (is_south_direction)
	{
		a_y = ceil(player->y);
		y_step = a_y - player->y;
		x_step = y_step / tan(ray->angle);
		a_x = player->x + x_step;
	}
	else
	{
		a_y = floor(player->y);
		y_step = player->y - a_y;
		x_step = y_step / tan(ray->angle);
		a_x = player->x - x_step;
	}
	ray->size += sqrt(pow(x_step, 2) + pow(y_step, 2));
	if (is_wall(map, a_x, is_south_direction ? a_y : a_y - 1, ray))
		return ;
	y_step = is_south_direction ? 1 : -1;
	x_step = y_step / tan(ray->angle);
	ray_section = sqrt(pow(x_step, 2) + pow(y_step, 2));
	while (!is_wall(map, a_x, is_south_direction ? a_y : a_y - 1, ray))
	{
		a_x += x_step;
		a_y += y_step;
		ray->size += ray_section;
	}
}

void	get_vrtl_intersection(t_ray *ray, t_map *map, t_player *player)
{
	const int	is_west_direction = is_west(ray->angle);

	double a_x, a_y, x_step, y_step, ray_section;
	ray->size = 0;
	if (ray->angle == deg2rad(90) || ray->angle == deg2rad(270))
	{
		ray->size = INT_MAX;
		return ;
	}
	if (is_west_direction)
	{
		a_x = floor(player->x);
		x_step = player->x - a_x;
		y_step = x_step * tan(ray->angle);
		a_y = player->y - y_step;
	}
	else
	{
		a_x = ceil(player->x);
		x_step = a_x - player->x;
		y_step = x_step * tan(ray->angle);
		a_y = player->y + y_step;
	}
	ray->size += sqrt(pow(x_step, 2) + pow(y_step, 2));
	if (is_west_direction ? is_wall(map, a_x - 1, a_y, ray) : is_wall(map, a_x,
			a_y, ray))
		return ;
	x_step = is_west_direction ? -1 : 1;
	y_step = x_step * tan(ray->angle);
	ray_section = sqrt(pow(x_step, 2) + pow(y_step, 2));
	while (!(is_west_direction ? is_wall(map, a_x - 1, a_y, ray) : is_wall(map,
				a_x, a_y, ray)))
	{
		a_x += x_step;
		a_y += y_step;
		ray->size += ray_section;
	}
}

void	cast_ray(t_ray *ray, t_map *map, t_player *player)
{
	t_ray	hrzn_intersection;
	t_ray	vrtl_intersection;

	hrzn_intersection.angle = normalize_radian(ray->angle);
	vrtl_intersection.angle = normalize_radian(ray->angle);
	hrzn_intersection.side = 'H';
	vrtl_intersection.side = 'V';
	get_hrzn_intersection(&hrzn_intersection, map, player);
	get_vrtl_intersection(&vrtl_intersection, map, player);
	if (hrzn_intersection.size <= vrtl_intersection.size)
		*ray = hrzn_intersection;
	else
		*ray = vrtl_intersection;
}
