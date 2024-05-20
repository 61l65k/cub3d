/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:48:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 17:50:23 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_helpers	init_raycast_helper_hrzn(t_raycast_helper *rh, t_ray *ray,
		t_player *player)
{
	if (ray->angle == deg2rad(180) || ray->angle == deg2rad(360))
	{
		ray->size = INT_MAX;
		return (IS_PERFECT_ANGLE);
	}
	rh->is_south_direction = is_south(ray->angle);
	ray->size = 0;
	if (rh->is_south_direction)
	{
		rh->a_y = ceil(player->y);
		rh->y_step = rh->a_y - player->y;
		rh->x_step = rh->y_step / tan(ray->angle);
		rh->a_x = player->x + rh->x_step;
	}
	else
	{
		rh->a_y = floor(player->y);
		rh->y_step = player->y - rh->a_y;
		rh->x_step = rh->y_step / tan(ray->angle);
		rh->a_x = player->x - rh->x_step;
	}
	ray->size += sqrt(pow(rh->x_step, 2) + pow(rh->y_step, 2));
	return (IS_NOT_PERFECT_ANGLE);
}

static t_helpers	init_raycast_helper_vrtl(t_raycast_helper *rh, t_ray *ray,
		t_player *player)
{
	if (ray->angle == deg2rad(90) || ray->angle == deg2rad(270))
	{
		ray->size = INT_MAX;
		return (IS_PERFECT_ANGLE);
	}
	rh->is_west_direction = is_west(ray->angle);
	ray->size = 0;
	if (rh->is_west_direction)
	{
		rh->a_x = floor(player->x);
		rh->x_step = player->x - rh->a_x;
		rh->y_step = rh->x_step * tan(ray->angle);
		rh->a_y = player->y - rh->y_step;
	}
	else
	{
		rh->a_x = ceil(player->x);
		rh->x_step = rh->a_x - player->x;
		rh->y_step = rh->x_step * tan(ray->angle);
		rh->a_y = player->y + rh->y_step;
	}
	ray->size += sqrt(pow(rh->x_step, 2) + pow(rh->y_step, 2));
	return (IS_NOT_PERFECT_ANGLE);
}

void	get_hrzn_intersection(t_ray *ray, t_map *map, t_player *player)
{
	t_raycast_helper	rh;

	if (init_raycast_helper_hrzn(&rh, ray, player) == IS_PERFECT_ANGLE
		|| (rh.is_south_direction && is_wall(map, rh.a_x, rh.a_y, ray))
		|| (!rh.is_south_direction && is_wall(map, rh.a_x, rh.a_y - 1, ray)))
		return ;
	if (rh.is_south_direction)
		rh.y_step = 1;
	else
		rh.y_step = -1;
	rh.x_step = rh.y_step / tan(ray->angle);
	rh.ray_section = sqrt(pow(rh.x_step, 2) + pow(rh.y_step, 2));
	while (1)
	{
		if (rh.is_south_direction)
		{
			if (is_wall(map, rh.a_x, rh.a_y, ray))
				break ;
		}
		if (is_wall(map, rh.a_x, rh.a_y - 1, ray))
			break ;
		rh.a_x += rh.x_step;
		rh.a_y += rh.y_step;
		ray->size += rh.ray_section;
	}
}

void	get_vrtl_intersection(t_ray *ray, t_map *map, t_player *player)
{
	t_raycast_helper	rh;

	if (init_raycast_helper_vrtl(&rh, ray, player) == IS_PERFECT_ANGLE
		|| (rh.is_west_direction && is_wall(map, rh.a_x - 1, rh.a_y, ray))
		|| (!rh.is_west_direction && is_wall(map, rh.a_x, rh.a_y, ray)))
		return ;
	if (rh.is_west_direction)
		rh.x_step = -1;
	else
		rh.x_step = 1;
	rh.y_step = rh.x_step * tan(ray->angle);
	rh.ray_section = sqrt(pow(rh.x_step, 2) + pow(rh.y_step, 2));
	while (1)
	{
		if (rh.is_west_direction)
		{
			if (is_wall(map, rh.a_x - 1, rh.a_y, ray))
				break ;
		}
		if (is_wall(map, rh.a_x, rh.a_y, ray))
			break ;
		rh.a_x += rh.x_step;
		rh.a_y += rh.y_step;
		ray->size += rh.ray_section;
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
