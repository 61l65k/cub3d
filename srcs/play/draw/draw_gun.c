/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:20:45 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 20:40:06 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_vertical_line(t_cubed *cubed, int draw_x, int draw_y, int color)
{
    if (draw_x >= 0 && draw_x < cubed->scene.resolution.width && 
        draw_y >= 0 && draw_y < cubed->scene.resolution.height)
    {
        cubed->mlx.img.data[draw_y * cubed->scene.resolution.width + draw_x] = color;
    }
}


void draw_gun(t_cubed *cubed)
{
    const t_texture     *gun_texture = &cubed->scene.gun_texture;
    const int           gun_pos_x = (cubed->scene.resolution.width - gun_texture->width) / 2;
    const int           gun_pos_y = cubed->scene.resolution.height - gun_texture->height + 50;
    int                 color;
    int                 x;
    int                 y;

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
}
