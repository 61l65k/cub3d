/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:24:06 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 23:20:07 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(t_rectangle *rec, int *img, int res_x)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < rec->height)
	{
		j = 0;
		while (j < rec->width)
		{
			x = rec->x + j;
			y = rec->y + i;
			img[y * res_x + x] = rec->fill_color;
			j++;
		}
		i++;
	}
}

void	draw_floor(t_cubed *cubed)
{
	t_rectangle	floor;

	floor.x = 0;
	floor.y = cubed->scene.resolution.height / 2;
	floor.width = cubed->scene.resolution.width;
	floor.height = (double)cubed->scene.resolution.height / 2;
	floor.border_width = 0;
	floor.fill_color = cubed->scene.floor_color.argb;
	floor.border_color = 0;
	draw_rectangle(&floor, cubed->mlx.img.data, cubed->scene.resolution.width);
}

void	draw_ceiling(t_cubed *cubed)
{
	t_rectangle	ceiling;

	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.width = cubed->scene.resolution.width;
	ceiling.height = (double)cubed->scene.resolution.height / 2;
	ceiling.border_width = 0;
	ceiling.fill_color = cubed->scene.ceiling_color.argb;
	ceiling.border_color = 0;
	draw_rectangle(&ceiling, cubed->mlx.img.data,
		cubed->scene.resolution.width);
}
