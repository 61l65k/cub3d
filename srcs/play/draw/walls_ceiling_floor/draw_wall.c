/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:18:22 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 11:37:28 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_x_offset(t_ray *ray, int texture_width)
{
	double	remainder;
	int		offset;

	if (ray->y == (int)ray->y)
		remainder = ray->x - floor(ray->x);
	else
		remainder = ray->y - floor(ray->y);
	offset = texture_width * remainder;
	return (offset);
}

static
void	render_wall_column(t_wall *wall, int *img, t_resolution *res,
		t_ray *ray)
{
	int				y;
	int				y_tex;
	const int		x_tex = get_texture_x_offset(ray, wall->texture.width);
	const double	step = 1.0 * wall->texture.height / wall->height;
	double			tex_pos;

	tex_pos = (wall->y - res->height / 2 + wall->height / 2) * step;
	y = 0;
	while (y < wall->height && wall->y + y < res->height)
	{
		if (wall->y + y >= 0)
		{
			y_tex = (int)tex_pos % (wall->texture.height - 1);
			tex_pos += step;
			if (y_tex >= 0 && y_tex < wall->texture.height)
			{
				img[(wall->y + y) * res->width
					+ wall->x] = wall->texture.img.data[y_tex
					* wall->texture.width + x_tex];
			}
		}
		y++;
	}
}

static
double	get_wall_height(t_cubed *cubed, t_ray *ray)
{
	const double	fisheye_adjustment = cos(ray->angle
			- cubed->player.rotation_angle);
	const double	scaled_distance = ray->distance * GRID_UNIT_SCALE
		* fisheye_adjustment;

	return ((GRID_UNIT_SCALE / scaled_distance)
		* (cubed->rays.proj_plane_dist));
}

static
t_texture	get_wall_texture(t_scenedata *scene, const t_ray *ray)
{
	if (ray->obstacle == '1')
	{
		if (ray->orientation == 'N')
			return (scene->north_texture);
		else if (ray->orientation == 'S')
			return (scene->south_texture);
		else if (ray->orientation == 'E')
			return (scene->east_texture);
		return (scene->west_texture);
	}
	else if (ray->obstacle == 'D')
	{
		if (ray->distance < 3)
			return (scene->sprite_info.door_open_texture);
		return (scene->sprite_info.door_closed_texture);
	}
	return (scene->north_texture);
}

void	draw_wall(t_cubed *cubed, t_ray *ray)
{
	t_wall	wall;

	if (ray->obstacle != '1' && ray->obstacle != 'D')
		return ;
	wall = (t_wall){0};
	wall.x = ray - cubed->rays.ray_array;
	wall.height = get_wall_height(cubed, ray);
	wall.y = (cubed->scene.resol.height / 2) - (wall.height / 2);
	if (wall.y < 0)
		wall.y = 0;
	wall.texture = get_wall_texture(&cubed->scene, ray);
	render_wall_column(&wall, cubed->mlx.img.data, &cubed->scene.resol, ray);
}
