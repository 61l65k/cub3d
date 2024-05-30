/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:53:30 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 13:32:35 by apyykone         ###   ########.fr       */
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
