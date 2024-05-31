/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 12:43:07 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sprite_calculate_tex_x(int stripe, t_sprite_render_info *info,
		t_texture *texture)
{
	const int	center_offset = stripe - (-info->sprite_width / 2
			+ info->sprite_screen_x);
	const int	scaled_texture_width = center_offset * texture->width;
	const int	tex_x = (int)(256 * scaled_texture_width / info->sprite_width)
		/ 256;

	return (tex_x);
}

static void	draw_sprite_line(t_cubed *cubed, int stripe,
		t_sprite_render_info *info, t_texture *texture)
{
	int			y;
	int			color;
	int			tex_y;
	int			d;
	const int	tex_x = sprite_calculate_tex_x(stripe, info, texture);

	y = info->draw_start_y - 1;
	while (++y < info->draw_end_y)
	{
		d = y * 256 - cubed->scene.resol.height * 128 + info->sprite_height
			* 128;
		tex_y = ((d * texture->height) / info->sprite_height) / 256;
		color = texture->img.data[texture->width * tex_y + tex_x];
		if (is_not_transparent(color))
		{
			draw_vertical_line(cubed, stripe, y, color);
		}
	}
}

static void	draw_healthbar_line(t_cubed *cubed, int stripe,
		t_sprite_render_info *info)
{
	int	health_bar_end_x;
	int	health_y;
	int	health_color;

	if (stripe >= info->health_bar.x && stripe < info->health_bar.x
		+ info->health_bar.width)
	{
		health_bar_end_x = info->health_bar.x + (int)(info->health_bar.width
				* info->health_bar.health_percentage);
		health_y = info->health_bar.y;
		while (health_y < info->health_bar.y + info->health_bar.height)
		{
			if (health_y >= 0 && health_y < cubed->scene.resol.height)
			{
				health_color = RED;
				if (stripe < health_bar_end_x)
					health_color = HBAR_GREEN;
				cubed->mlx.img.data[health_y * cubed->scene.resol.width
					+ stripe] = health_color;
			}
			health_y++;
		}
	}
}

static void	draw_line(t_cubed *cubed, int stripe, t_sprite_render_info *info,
		t_texture *texture)
{
	draw_sprite_line(cubed, stripe, info, texture);
	draw_healthbar_line(cubed, stripe, info);
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
			draw_line(cubed, stripe, info, texture);
		}
	}
}
