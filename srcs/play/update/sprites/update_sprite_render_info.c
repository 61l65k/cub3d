/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_render_info.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:02:32 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 12:37:22 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_health_bar(t_sprite_render_info *i, int screen_width,
		int screen_height)
{
	i->health_bar.width = screen_width / 20;
	i->health_bar.height = screen_height / 100;
	i->health_bar.x = i->sprite_screen_x - i->health_bar.width / 2;
	i->health_bar.y = i->draw_start_y - i->health_bar.height - 5;
	if (i->health_bar.initialized == false)
	{
		i->health_bar.health_percentage = 1.0;
		i->health_bar.initialized = true;
	}
}

static void	calculate_transform(t_cubed *cubed, double sprite_x,
		double sprite_y, t_sprite_render_info *i)
{
	double	inv_det;

	sprite_x -= cubed->player.x;
	sprite_y -= cubed->player.y;
	inv_det = 1.0 / (cubed->player.plane_x * cubed->player.dir_y
			- cubed->player.dir_x * cubed->player.plane_y);
	i->transform_x = inv_det * (cubed->player.dir_y * sprite_x
			- cubed->player.dir_x * sprite_y);
	i->transform_y = inv_det * (-cubed->player.plane_y * sprite_x
			+ cubed->player.plane_x * sprite_y);
	i->sprite_screen_x = (int)((cubed->scene.resol.width / 2) * (1
				+ i->transform_x / i->transform_y));
}

static void	calculate_draw_boundaries(t_cubed *cubed, t_sprite_render_info *i)
{
	i->sprite_height = abs((int)(cubed->scene.resol.height / i->transform_y));
	i->sprite_width = i->sprite_height;
	i->draw_start_y = -i->sprite_height / 2 + cubed->scene.resol.height / 2;
	if (i->draw_start_y < 0)
		i->draw_start_y = 0;
	i->draw_end_y = i->sprite_height / 2 + cubed->scene.resol.height / 2;
	if (i->draw_end_y >= cubed->scene.resol.height)
		i->draw_end_y = cubed->scene.resol.height - 1;
	i->draw_start_x = -i->sprite_width / 2 + i->sprite_screen_x;
	if (i->draw_start_x < 0)
		i->draw_start_x = 0;
	i->draw_end_x = i->sprite_width / 2 + i->sprite_screen_x;
	if (i->draw_end_x >= cubed->scene.resol.width)
		i->draw_end_x = cubed->scene.resol.width - 1;
	update_health_bar(i, cubed->scene.resol.width, cubed->scene.resol.height);
}

void	update_render_info(t_cubed *cubed, double sprite_x, double sprite_y,
		t_sprite_render_info *info)
{
	calculate_transform(cubed, sprite_x, sprite_y, info);
	calculate_draw_boundaries(cubed, info);
}
