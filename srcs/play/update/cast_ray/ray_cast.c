/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:48:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 10:57:54 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ray_cast_internal.h"

static void	init_x_intersection_helper(t_raycast_helper *rh, t_ray *ray,
		const t_player *player)
{
	const bool	is_south = (0 <= ray->angle && ray->angle < M_PI);

	if (is_south)
	{
		ray->orientation = 'S';
		ray->y = ceil(player->y);
		rh->y_step = ray->y - player->y;
		rh->x_step = rh->y_step / tan(ray->angle);
		ray->x = player->x + rh->x_step;
		ray->distance = hypot(rh->x_step, rh->y_step);
		rh->y_step = 1;
	}
	else
	{
		ray->orientation = 'N';
		ray->y = floor(player->y);
		rh->y_step = player->y - ray->y;
		rh->x_step = rh->y_step / tan(ray->angle);
		ray->x = player->x - rh->x_step;
		ray->distance = hypot(rh->x_step, rh->y_step);
		rh->y_step = -1;
		ray->y -= 1;
	}
	rh->x_step = rh->y_step / tan(ray->angle);
	rh->ray_section = hypot(rh->x_step, rh->y_step);
}

static void	init_y_intersection_helper(t_raycast_helper *rh, t_ray *ray,
		const t_player *player)
{
	const bool	is_east = (M_PI / 2 > ray->angle || ray->angle > M_PI * 1.5);

	if (is_east)
	{
		ray->orientation = 'E';
		ray->x = ceil(player->x);
		rh->x_step = ray->x - player->x;
		rh->y_step = rh->x_step * tan(ray->angle);
		ray->y = player->y + rh->y_step;
		ray->distance = hypot(rh->x_step, rh->y_step);
		rh->x_step = 1;
	}
	else
	{
		ray->orientation = 'W';
		ray->x = floor(player->x);
		rh->x_step = player->x - ray->x;
		rh->y_step = rh->x_step * tan(ray->angle);
		ray->y = player->y - rh->y_step;
		ray->distance = hypot(rh->x_step, rh->y_step);
		rh->x_step = -1;
		ray->x -= 1;
	}
	rh->y_step = rh->x_step * tan(ray->angle);
	rh->ray_section = hypot(rh->x_step, rh->y_step);
}

static void	perform_dda(t_ray *ray, const t_map *map, const t_player *player,
	int side)
{
	t_raycast_helper	rh;

	if (side == Y_AXIS_INTERSECTION)
		init_y_intersection_helper(&rh, ray, player);
	else
		init_x_intersection_helper(&rh, ray, player);
	while (1)
	{
		ray->obstacle = t_map_get_f(map, ray->x, ray->y);
		if (ray->obstacle == '\0')
		{
			break ;
		}
		if (ray->obstacle == '1')
			break ;
		if (ray->obstacle == 'D' && ray->distance > DOOR_OPENING_DISTANCE)
			break ;
		ray->x += rh.x_step;
		ray->y += rh.y_step;
		ray->distance += rh.ray_section;
	}
}

void	update_rays(t_rays *rays, const t_map *map, const t_player *player)
{
	double			ray_angle;
	int				i;
	t_ray			y_axis_intersection;
	const double	ray_angle_step = player->fov_rad / rays->ray_count;

	ray_angle = player->rotation_angle - player->fov_rad / 2;
	i = -1;
	while (++i < rays->ray_count)
	{
		y_axis_intersection.angle = normalize_radian(ray_angle);
		rays->ray_array[i].angle = y_axis_intersection.angle;
		perform_dda(&rays->ray_array[i], map, player, X_AXIS_INTERSECTION);
		perform_dda(&y_axis_intersection, map, player, Y_AXIS_INTERSECTION);
		if (y_axis_intersection.distance < rays->ray_array[i].distance)
			rays->ray_array[i] = y_axis_intersection;
		ray_angle += ray_angle_step;
	}
	rays->proj_plane_dist
		= (rays->ray_count / 2.0) / player->fov_scaling_factor;
}
