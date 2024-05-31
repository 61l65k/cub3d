/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:48:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 12:24:06 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ray_cast_internal.h"

static void	init_x_intersection_helper(t_raycast_helper *rh, t_ray *ray,
		const t_player *player)
{
	rh->is_south_direction = (0 <= ray->angle && ray->angle < M_PI);
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
	ray->distance = get_hypotenuse(rh->x_step, rh->y_step);
	if (rh->is_south_direction)
		rh->y_step = 1;
	else
	{
		rh->y_step = -1;
		rh->a_y -= 1;
	}
	rh->x_step = rh->y_step / tan(ray->angle);
	rh->ray_section = get_hypotenuse(rh->x_step, rh->y_step);
}

static void	get_x_intersection(t_ray *ray, const t_map *map,
		const t_player *player)
{
	t_raycast_helper	rh;

	init_x_intersection_helper(&rh, ray, player);
	ray->x = rh.a_x;
	ray->y = rh.a_y;
	while (1)
	{
		ray->obstacle = t_map_get_f(map, ray->x, ray->y);
		if (ray->obstacle == '\0')
		{
			ray->distance = INT_MAX;
			break ;
		}
		if (ray->obstacle == '1' || ray->obstacle == 'D')
		{
			if (rh.is_south_direction)
				ray->orientation = 'S';
			else
				ray->orientation = 'N';
			break ;
		}
		ray->x += rh.x_step;
		ray->y += rh.y_step;
		ray->distance += rh.ray_section;
	}
}

static void	init_y_intersection_helper(t_raycast_helper *rh, t_ray *ray,
		const t_player *player)
{
	rh->is_east_direction = (M_PI / 2 > ray->angle || ray->angle > M_PI * 1.5);
	if (rh->is_east_direction)
	{
		rh->a_x = ceil(player->x);
		rh->x_step = rh->a_x - player->x;
		rh->y_step = rh->x_step * tan(ray->angle);
		rh->a_y = player->y + rh->y_step;
	}
	else
	{
		rh->a_x = floor(player->x);
		rh->x_step = player->x - rh->a_x;
		rh->y_step = rh->x_step * tan(ray->angle);
		rh->a_y = player->y - rh->y_step;
	}
	ray->distance = get_hypotenuse(rh->x_step, rh->y_step);
	if (rh->is_east_direction)
		rh->x_step = 1;
	else
	{
		rh->x_step = -1;
		rh->a_x -= 1;
	}
	rh->y_step = rh->x_step * tan(ray->angle);
	rh->ray_section = get_hypotenuse(rh->x_step, rh->y_step);
}

static void	get_y_intersection(t_ray *ray, const t_map *map,
	const t_player *player)
{
	t_raycast_helper	rh;

	init_y_intersection_helper(&rh, ray, player);
	ray->x = rh.a_x;
	ray->y = rh.a_y;
	while (1)
	{
		ray->obstacle = t_map_get_f(map, ray->x, ray->y);
		if (ray->obstacle == '\0')
		{
			ray->distance = INT_MAX;
			break ;
		}
		if (ray->obstacle == '1' || ray->obstacle == 'D')
		{
			if (rh.is_east_direction)
				ray->orientation = 'E';
			else
				ray->orientation = 'W';
			break ;
		}
		ray->x += rh.x_step;
		ray->y += rh.y_step;
		ray->distance += rh.ray_section;
	}
}

void	update_rays(t_cubed *cubed)
{
	double			ray_angle;
	int				i;
	t_ray			x_intersection;
	t_ray			y_intersection;
	const double	ray_angle_step = cubed->rays.field_of_view
		/ cubed->scene.resol.width;

	x_intersection.side = 'H';
	y_intersection.side = 'V';
	ray_angle = cubed->player.rotation_angle - cubed->rays.field_of_view / 2;
	i = -1;
	while (++i < cubed->scene.resol.width)
	{
		x_intersection.angle = normalize_radian(ray_angle);
		y_intersection.angle = x_intersection.angle;
		x_intersection.orientation = 0;
		y_intersection.orientation = 0;
		get_x_intersection(&x_intersection, &cubed->scene.map, &cubed->player);
		get_y_intersection(&y_intersection, &cubed->scene.map, &cubed->player);
		if (x_intersection.distance <= y_intersection.distance)
			cubed->rays.ray_array[i] = x_intersection;
		else
			cubed->rays.ray_array[i] = y_intersection;
		ray_angle += ray_angle_step;
	}
}
