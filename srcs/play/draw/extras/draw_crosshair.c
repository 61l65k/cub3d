/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:12:36 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 23:29:42 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizontal_line_crosshair(t_cubed *cubed, const t_point center,
		int size, int color)
{
	int		offset;
	t_point	pixel;

	offset = -size;
	while (offset <= size)
	{
		pixel.x = center.x + offset;
		pixel.y = center.y;
		if (pixel.x >= 0 && pixel.x < cubed->scene.resol.width && pixel.y >= 0
			&& pixel.y < cubed->scene.resol.height)
		{
			cubed->mlx.img.data[(int)pixel.y * cubed->scene.resol.width
				+ (int)pixel.x] = color;
		}
		offset++;
	}
}

static void	draw_vertical_line_crosshair(t_cubed *cubed, const t_point center,
		int size, int color)
{
	int		offset;
	t_point	pixel;

	offset = -size;
	while (offset <= size)
	{
		pixel.x = center.x;
		pixel.y = center.y + offset;
		if (pixel.x >= 0 && pixel.x < cubed->scene.resol.width && pixel.y >= 0
			&& pixel.y < cubed->scene.resol.height)
		{
			cubed->mlx.img.data[(int)pixel.y * cubed->scene.resol.width
				+ (int)pixel.x] = color;
		}
		offset++;
	}
}

void	draw_crosshair(t_cubed *cubed)
{
	const int		crosshair_size = 10;
	const t_point	center = {(float)cubed->scene.resol.width / 2,
		(float)cubed->scene.resol.height / 2};
	const int		color = RED;

	draw_horizontal_line_crosshair(cubed, center, crosshair_size, color);
	draw_vertical_line_crosshair(cubed, center, crosshair_size, color);
}
