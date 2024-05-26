/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_render_info.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:02:32 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 11:49:13 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_transform(t_cubed *cubed, double sprite_x,
		double sprite_y, t_sprite_render_info *transform)
{
	double	inv_det;

	sprite_x -= cubed->player.x;
	sprite_y -= cubed->player.y;
	inv_det = 1.0 / (cubed->player.plane_x * cubed->player.dir_y
			- cubed->player.dir_x * cubed->player.plane_y);
	transform->transform_x = inv_det * (cubed->player.dir_y * sprite_x
			- cubed->player.dir_x * sprite_y);
	transform->transform_y = inv_det * (-cubed->player.plane_y * sprite_x
			+ cubed->player.plane_x * sprite_y);
	transform->sprite_screen_x = (int)((cubed->scene.resol.width / 2) * (1
				+ transform->transform_x / transform->transform_y));
}

static void	calculate_draw_boundaries(t_cubed *cubed,
		t_sprite_render_info *info)
{
	info->sprite_height = abs((int)(cubed->scene.resol.height
				/ info->transform_y));
	info->sprite_width = info->sprite_height;
	info->draw_start_y = -info->sprite_height / 2 + cubed->scene.resol.height
		/ 2;
	if (info->draw_start_y < 0)
		info->draw_start_y = 0;
	info->draw_end_y = info->sprite_height / 2 + cubed->scene.resol.height / 2;
	if (info->draw_end_y >= cubed->scene.resol.height)
		info->draw_end_y = cubed->scene.resol.height - 1;
	info->draw_start_x = -info->sprite_width / 2 + info->sprite_screen_x;
	if (info->draw_start_x < 0)
		info->draw_start_x = 0;
	info->draw_end_x = info->sprite_width / 2 + info->sprite_screen_x;
	if (info->draw_end_x >= cubed->scene.resol.width)
		info->draw_end_x = cubed->scene.resol.width - 1;
}

void	update_render_info(t_cubed *cubed, double sprite_x, double sprite_y,
		t_sprite_render_info *info)
{
	calculate_transform(cubed, sprite_x, sprite_y, info);
	calculate_draw_boundaries(cubed, info);
}
