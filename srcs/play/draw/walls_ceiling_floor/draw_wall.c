/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:18:22 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 14:55:54 by ttakala          ###   ########.fr       */
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
void	render_wall_column(const t_wall *wall, int *img,
		const t_resolution *res, const t_texture *texture)
{
	int				y;
	int				y_tex;
	const double	step = texture->height / wall->height;
	double			tex_pos;

	tex_pos = (wall->y - res->height / 2.0 + wall->height / 2) * step;
	y = 0;
	while (y < wall->height && wall->y + y < res->height && wall->y + y >= 0)
	{
		y_tex = (int)tex_pos % (texture->height - 1);
		tex_pos += step;
		if (y_tex >= 0 && y_tex < texture->height)
		{
			img[(wall->y + y) * res->width + wall->x]
				= texture->img.data[y_tex * texture->width + wall->x_tex];
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
	wall.height = 1
		/ (ray->distance * cos(ray->angle - cubed->player.rotation_angle))
		* cubed->rays.proj_plane_dist;
	wall.y = (cubed->scene.resol.height - wall.height) / 2;
	if (wall.y < 0)
		wall.y = 0;
	texture = get_wall_texture(&cubed->scene, ray);
	if (ray->y == floor(ray->y))
		wall.x_tex = (ray->x - floor(ray->x)) * texture.width;
	else
		wall.x_tex = (ray->y - floor(ray->y)) * texture.width;
	render_wall_column(&wall, cubed->mlx.img.data,
		&cubed->scene.resol, &texture);
}
