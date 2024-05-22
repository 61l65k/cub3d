/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:20:45 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 14:23:50 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_line(t_cubed *cubed, int draw_x, int draw_y,
		int color)
{
	if (draw_x >= 0 && draw_x < cubed->scene.resol.width && draw_y >= 0
		&& draw_y < cubed->scene.resol.height)
	{
		cubed->mlx.img.data[draw_y * cubed->scene.resol.width
			+ draw_x] = color;
	}
}


void draw_gun_shooting(t_cubed *cubed)
{
    t_weapon_map *weapon_map = &cubed->scene.weapon_map;
    t_weapon *current_weapon = &weapon_map->weapons[weapon_map->current_weapon];
    const t_texture *gun_texture = &current_weapon->texture;
    const int gun_pos_x = (cubed->scene.resol.width - gun_texture->width) / 2;
    const int gun_pos_y = cubed->scene.resol.height - gun_texture->height + 50;
    int color;
    int x, y;
    int left_gun_tip_x;
    int right_gun_tip_x;
    int gun_tip_y;

    for (y = 0; y < gun_texture->height; y++)
    {
        for (x = 0; x < gun_texture->width; x++)
        {
            color = gun_texture->img.data[y * gun_texture->width + x];
            if ((unsigned int)color != 0xFF000000)
                draw_vertical_line(cubed, gun_pos_x + x, gun_pos_y + y, color);
        }
    }

    if (cubed->player.shooting)
    {
        t_animation *animation = &current_weapon->shooting_animation;
        const t_texture *current_frame = &animation->frames[animation->curr_frame];

        left_gun_tip_x = gun_pos_x + gun_texture->width * 0.2;
        right_gun_tip_x = gun_pos_x + gun_texture->width * 0.78;
        gun_tip_y = gun_pos_y + gun_texture->height * 0.3;

        for (y = 0; y < current_frame->height; y++)
        {
            for (x = 0; x < current_frame->width; x++)
            {
                color = current_frame->img.data[y * current_frame->width + x];
                if ((unsigned int)color != 0xFF000000)
                {
                    draw_vertical_line(cubed, left_gun_tip_x + x, gun_tip_y + y, color);
                    draw_vertical_line(cubed, right_gun_tip_x + x, gun_tip_y + y, color);
                }
            }
        }
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
}
