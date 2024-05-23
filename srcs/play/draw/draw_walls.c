/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:18:22 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/23 11:57:15 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_height(t_cubed *cubed, t_ray *ray)
{
	const double	fisheye_adjustment = cos(ray->angle
				- cubed->player.rotation_angle);
	const double	scaled_distance = ray->size * GRID_UNIT_SCALE
		* fisheye_adjustment;

	// printf("ROTA: %f\n", cubed->player.rotation_angle);
	return ((GRID_UNIT_SCALE / scaled_distance) * (cubed->rays.proj_plane_dist));
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

void	draw_walls(t_cubed *game)
{
	int		i;
	t_wall	wall;
	t_ray	*ray;

	i = 0;
	wall = (t_wall){0};
	while (i < game->scene.resol.width)
	{
		ray = &game->rays.ray_array[i];
		wall.x = i;
		wall.height = get_wall_height(game, ray);
		wall.y = get_y_wall_position(game, wall.height);
		wall.texture = get_wall_texture(&game->scene, ray->orientation);
		render_wall_column(&wall, game->mlx.img.data, &game->scene.resol, ray);
		i++;
	}
}
