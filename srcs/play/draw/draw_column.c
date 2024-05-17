/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:53:30 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/17 14:25:05 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_x_offset(t_ray *ray, int texture_width)
{
	double	remainder;
	int		offset;

	if (ray->side == 'H')
		remainder = ray->x - floor(ray->x);
	else
		remainder = ray->y - floor(ray->y);
	offset = texture_width * remainder;
	return (offset);
}

void	render_wall_column(t_wall *wall, int *img, t_resolution *res,
		t_ray *ray)
{
	int		y;
	int		y_tex;
	int		x_tex;
	double	step;
	double	tex_pos;

	step = 1.0 * wall->texture.height / wall->height;
	tex_pos = (wall->y - (int)res->height / 2 + wall->height / 2) * step;
	x_tex = get_texture_x_offset(ray, wall->texture.width);
	y = -1;
	while (++y < wall->height && y < res->height)
	{
		y_tex = (int)tex_pos & (wall->texture.height - 1);
		tex_pos += step;
		img[(wall->y * res->width) + (y * res->width)
			+ wall->x] = wall->texture.img.data[y_tex * wall->texture.width
			+ x_tex];
	}
}
