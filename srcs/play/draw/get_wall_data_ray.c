/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_data_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:18:22 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/29 12:52:16 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_height(t_cubed *cubed, t_ray *ray)
{
	const double	fisheye_adjustment = cos(ray->angle
				- cubed->player.rotation_angle);
	const double	scaled_distance = ray->distance * GRID_UNIT_SCALE
			* fisheye_adjustment;

	return ((GRID_UNIT_SCALE / scaled_distance)
		* (cubed->rays.proj_plane_dist));
}

int	get_y_wall_position(t_cubed *cubed, double wall_height)
{
	const int	center_screen = cubed->scene.resol.height / 2;
	int			y;

	y = center_screen - (wall_height / 2);
	if (y < 0)
		y = 0;
	return (y);
}

t_texture	get_wall_texture(t_scenedata *scene, char orientation)
{
	if (orientation == 'N')
		return (scene->north_texture);
	else if (orientation == 'S')
		return (scene->south_texture);
	else if (orientation == 'E')
		return (scene->east_texture);
	return (scene->west_texture);
}
