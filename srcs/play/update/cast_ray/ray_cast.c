/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:48:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/29 15:57:15 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door				*find_door(t_cubed *cubed, int map_x, int map_y);
int					ray_check_door(t_cubed *cubed, t_ray *closest_intersection,
						int i, double *ray_angle);

static t_helpers	init_raycast_helper_hrzn(t_raycast_helper *rh, t_ray *ray,
		t_player *player)
{
	if (ray->angle == deg2rad(180) || ray->angle == deg2rad(360))
	{
		ray->distance = INT_MAX;
		return (IS_PERFECT_ANGLE);
	}
	rh->is_south_direction = is_ray_facing_south(ray->angle);
	ray->distance = 0;
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
	ray->distance += get_hypotenuse(rh->x_step, rh->y_step);
	return (IS_NOT_PERFECT_ANGLE);
}

static t_helpers	init_raycast_helper_vrtl(t_raycast_helper *rh, t_ray *ray,
		t_player *player)
{
	if (ray->angle == deg2rad(90) || ray->angle == deg2rad(270))
	{
		ray->distance = INT_MAX;
		return (IS_PERFECT_ANGLE);
	}
	rh->is_west_direction = is_ray_facing_west(ray->angle);
	ray->distance = 0;
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
	ray->distance += get_hypotenuse(rh->x_step, rh->y_step);
	return (IS_NOT_PERFECT_ANGLE);
}

static void	get_x_intersection(t_ray *ray, t_map *map, t_player *player)
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
	rh.ray_section = get_hypotenuse(rh.x_step, rh.y_step);
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
		ray->distance += rh.ray_section;
	}
}

static void	get_y_intersection(t_ray *ray, t_map *map, t_player *player)
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
	rh.ray_section = get_hypotenuse(rh.x_step, rh.y_step);
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
		ray->distance += rh.ray_section;
	}
}

void	update_rays(t_cubed *cubed)
{
	double	ray_angle;
	int		i;
	t_ray	x_intersection;
	t_ray	y_intersection;

	x_intersection.side = 'H';
	y_intersection.side = 'V';
	ray_angle = cubed->player.rotation_angle - cubed->rays.field_of_view / 2;
	i = -1;
	while (++i < cubed->scene.resol.width)
	{
		x_intersection.angle = normalize_radian(ray_angle);
		y_intersection.angle = normalize_radian(ray_angle);
		x_intersection.orientation = 0;
		y_intersection.orientation = 0;
		get_x_intersection(&x_intersection, &cubed->scene.map, &cubed->player);
		get_y_intersection(&y_intersection, &cubed->scene.map, &cubed->player);
		if (x_intersection.distance <= y_intersection.distance)
			cubed->rays.ray_array[i] = x_intersection;
		else
			cubed->rays.ray_array[i] = y_intersection;
		ray_angle += cubed->rays.field_of_view / cubed->scene.resol.width;
	}
}
