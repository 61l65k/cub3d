/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:20:45 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/23 14:06:22 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_line(t_cubed *cubed, int draw_x, int draw_y,
		int color)
{
	if (draw_x >= 0 && draw_x < cubed->scene.resol.width && draw_y >= 0
		&& draw_y < cubed->scene.resol.height)
	{
		cubed->mlx.img.data[draw_y * cubed->scene.resol.width + draw_x] = color;
	}
}

static void	draw_gun(t_cubed *cubed, t_weapon *weapon)
{
	const t_texture	*gun_texture = &weapon->texture;
	int				color;
	int				x;
	int				y;

	y = -1;
	while (++y < gun_texture->height)
	{
		x = -1;
		while (++x < gun_texture->width)
		{
			color = gun_texture->img.data[y * gun_texture->width + x];
			if ((unsigned int)color != 0xFF000000)
				draw_vertical_line(cubed, weapon->gun_pos_x + x,
					weapon->gun_pos_y + y, color);
		}
	}
}

static void	draw_shooting_effect(t_cubed *cubed, t_weapon *weapon)
{
	const t_animation	*animation = &weapon->shooting_animation;
	const t_texture		*current_frame = &animation->frames[animation->curr_frame];
	int					color;
	int					x;
	int					y;

	y = -1;
	while (++y < current_frame->height)
	{
		x = -1;
		while (++x < current_frame->width)
		{
			color = current_frame->img.data[y * current_frame->width + x];
			if ((unsigned int)color != 0xFF000000)
			{
				draw_vertical_line(cubed, weapon->left_gun_tip_x + x,
					weapon->gun_tip_y + y, color);
				draw_vertical_line(cubed, weapon->right_gun_tip_x + x,
					weapon->gun_tip_y + y, color);
			}
		}
	}
}

static void	update_shooting_animation(t_cubed *cubed, t_weapon *weapon)
{
	t_animation	*animation;

	animation = &weapon->shooting_animation;
	animation->frame_timer++;
	if (animation->frame_timer >= animation->frame_delay)
	{
		animation->frame_timer = 0;
		animation->curr_frame++;
		if (animation->curr_frame >= animation->frame_count)
		{
			animation->curr_frame = 0;
			cubed->player.shooting = 0;
		}
	}
}

void	draw_gun_shooting(t_cubed *cubed)
{
	t_weapon_map	*weapon_map;
	t_weapon		*current_weapon;

	weapon_map = &cubed->scene.weapon_map;
	current_weapon = &weapon_map->weapons[weapon_map->current_weapon];
	draw_gun(cubed, current_weapon);
	if (cubed->player.shooting)
	{
		draw_shooting_effect(cubed, current_weapon);
		update_shooting_animation(cubed, current_weapon);
	}
}
