/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:18:22 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/17 05:34:44 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_bitmap_offset(t_ray *ray, int bitmap_width)
{
	double	remainder;
	int		offset;

	if (ray->side == 'H')
	{
		remainder = ray->x - floor(ray->x);
		offset = bitmap_width * remainder;
	}
	else
	{
		remainder = ray->y - floor(ray->y);
		offset = bitmap_width * remainder;
	}
	return (offset);
}

void	draw_wall_strip(t_wall *rect, int *img, t_resolution *res, t_ray *ray)
{
	int		y;
	int		y_tex;
	int		x_tex;
	double	step;
	double	tex_pox;

	step = 1.0 * rect->texture.height / rect->height;
	tex_pox = (rect->y - (int)res->height / 2 + rect->height / 2) * step;
	x_tex = get_bitmap_offset(ray, rect->texture.width);
	y = -1;
	while (++y < rect->height && y < res->height)
	{
		y_tex = (int)tex_pox & (rect->texture.height - 1);
		tex_pox += step;
		img[(rect->y * res->width) + (y * res->width)
			+ rect->x] = rect->texture.img.data[y_tex * rect->texture.height
			+ x_tex];
	}
}

double	get_wall_height(t_cubed *game, t_ray *ray)
{
	const double	fisheye_adjustment = cos(ray->angle
				- game->player.rotation_angle);
	const double	scaled_distance = ray->size * GRID_UNIT_SCALE
			* fisheye_adjustment;

	return ((GRID_UNIT_SCALE / scaled_distance) * game->rays.dist_proj_plane);
}

int	get_y_wall_position(t_cubed *cubed, double wall_height)
{
	const int	center_screen = cubed->scene.resolution.height / 2;
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
	else
		return (scene->west_texture);
}

void	draw_walls(t_cubed *game)
{
	int		i;
	t_wall	wall;
	t_ray	*ray;

	i = 0;
	wall = (t_wall){0};
	while (i < game->scene.resolution.width)
	{
		ray = &game->rays.ray_array[i];
		wall.x = i;
		wall.height = get_wall_height(game, ray);
		wall.y = get_y_wall_position(game, wall.height);
		wall.texture = get_wall_texture(&game->scene, ray->orientation);
		draw_wall_strip(&wall, game->mlx.img.data, &game->scene.resolution,
			ray);
		i++;
	}
}
