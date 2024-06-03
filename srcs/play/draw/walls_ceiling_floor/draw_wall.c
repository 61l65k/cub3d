/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:18:22 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 12:12:32 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_wall.h"

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

static
double	get_wall_height(const t_cubed *cubed, const t_ray *ray)
{
	const double	fisheye_adjustment = cos(ray->angle
			- cubed->player.rotation_angle);
	const double	scaled_distance = ray->distance * GRID_UNIT_SCALE
		* fisheye_adjustment;

	return ((GRID_UNIT_SCALE / scaled_distance)
		* (cubed->rays.proj_plane_dist));
}

static int	get_texture_x_offset(const t_ray *ray, int texture_width)
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
void	render_wall_column(const t_wall *wall, int *img,
		const t_resolution *res, const t_texture *texture)
{
	int				y;
	int				y_tex;
	const double	step = 1.0 * texture->height / wall->height;
	double			tex_pos;

	tex_pos = (wall->y - res->height / 2 + wall->height / 2) * step;
	y = 0;
	while (y < wall->height && wall->y + y < res->height)
	{
		if (wall->y + y >= 0)
		{
			y_tex = (int)tex_pos % (texture->height - 1);
			tex_pos += step;
			if (y_tex >= 0 && y_tex < texture->height)
			{
				img[(wall->y + y) * res->width
					+ wall->x] = texture->img.data[y_tex
					* texture->width + wall->x_tex];
			}
		}
		y++;
	}
}

void	draw_wall(t_cubed *cubed, t_ray *ray)
{
	t_wall		wall;
	t_texture	texture;

	if (ray->obstacle != '1' && ray->obstacle != 'D')
		return ;
	wall.x = ray - cubed->rays.ray_array;
	wall.height = get_wall_height(cubed, ray);
	wall.y = (cubed->scene.resol.height - wall.height) / 2;
	if (wall.y < 0)
		wall.y = 0;
	texture = get_wall_texture(&cubed->scene, ray);
	wall.x_tex = get_texture_x_offset(ray, texture.width);
	render_wall_column(&wall, cubed->mlx.img.data,
		&cubed->scene.resol, &texture);
}
