/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 11:36:00 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_sprite_line(t_cubed *cubed, int stripe,
		t_sprite_render_info *info, t_texture *texture)
{
	int			d;
	int			tex_y;
	int			y;
	const int	tex_x = calculate_tex_x(stripe, info, texture);
	int			color;

	y = info->draw_start_y - 1;
	while (++y < info->draw_end_y)
	{
		d = y * 256 - cubed->scene.resol.height * 128 + info->sprite_height
			* 128;
		tex_y = ((d * texture->height) / info->sprite_height) / 256;
		color = texture->img.data[texture->width * tex_y + tex_x];
		if (is_not_transparent(color))
			draw_vertical_line(cubed, stripe, y, color);
	}
}

void	draw_any_sprite(t_cubed *cubed, t_sprite_render_info *info,
		t_texture *texture)
{
	int	stripe;

	stripe = info->draw_start_x - 1;
	while (++stripe < info->draw_end_x)
	{
		if (info->transform_y > 0 && stripe > 0
			&& stripe < cubed->scene.resol.width)
		{
			draw_vertical_sprite_line(cubed, stripe, info, texture);
		}
	}
}
