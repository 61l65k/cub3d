/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:20:45 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 22:24:04 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_line(t_cubed *cubed, int draw_x, int draw_y,
		int color)
{
	if (draw_x >= 0 && draw_x < cubed->scene.resolution.width && draw_y >= 0
		&& draw_y < cubed->scene.resolution.height)
	{
		cubed->mlx.img.data[draw_y * cubed->scene.resolution.width
			+ draw_x] = color;
	}
}

static void	draw_shooting_animation(t_cubed *cubed, int color, int gun_pos_x,
		int gun_pos_y)
{
	int				x;
	int				y;
	const t_texture	*shoot_text = &cubed->scene.shooting_animation.frames[cubed->scene.shooting_animation.curr_frame];

	y = 0;
	while (y < shoot_text->height)
	{
		x = 0;
		while (x < shoot_text->width)
		{
			color = shoot_text->img.data[y * shoot_text->width + x];
			if ((unsigned int)color != 0xFF000000)
				draw_vertical_line(cubed, gun_pos_x + x, gun_pos_y + y, color);
			x++;
		}
		y++;
	}
	if (cubed->scene.shooting_animation.curr_frame == cubed->scene.shooting_animation.frame_count
		- 1)
		cubed->player.shooting = 0;
}

void	draw_gun_shooting(t_cubed *cubed)
{
	const t_texture	*gun_texture = &cubed->scene.gun_texture;
	const int		gun_pos_x = (cubed->scene.resolution.width
					- gun_texture->width) / 2;
	const int		gun_pos_y = cubed->scene.resolution.height
				- gun_texture->height + 50;
	int				color;
	int				x;
	int				y;
	int				left_gun_tip_x;
	int				right_gun_tip_x;
	int				gun_tip_y;

	y = 0;
	while (y < gun_texture->height)
	{
		x = 0;
		while (x < gun_texture->width)
		{
			color = gun_texture->img.data[y * gun_texture->width + x];
			if ((unsigned int)color != 0xFF000000)
				draw_vertical_line(cubed, gun_pos_x + x, gun_pos_y + y, color);
			x++;
		}
		y++;
	}
	if (cubed->player.shooting)
	{
		left_gun_tip_x = gun_pos_x + gun_texture->width * 0.2;
		right_gun_tip_x = gun_pos_x + gun_texture->width * 0.78;
		gun_tip_y = gun_pos_y + gun_texture->height * 0.3;
		draw_shooting_animation(cubed, color, left_gun_tip_x, gun_tip_y);
		draw_shooting_animation(cubed, color, right_gun_tip_x, gun_tip_y);
	}
}
