/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_render_info.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:02:32 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 12:42:19 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_health_bar(t_sprite_render_info *i, const t_resolution *res)
{
	i->health_bar.width = res->width / 20;
	i->health_bar.height = res->height / 100;
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
	const t_player	*p = &cubed->player;
	const double	inv_d = 1 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);

	sprite_x -= p->x;
	sprite_y -= p->y;
	i->transform_x = inv_d * (p->dir_y * sprite_x - p->dir_x * sprite_y);
	i->transform_y = inv_d * (-p->plane_y * sprite_x + p->plane_x * sprite_y);
	i->sprite_screen_x = (int)((int)(cubed->scene.resol.width / 2) * (1
				+ i->transform_x / i->transform_y));
}

static void	calculate_draw_boundaries(t_cubed *cubed, t_sprite_render_info *i)
{
	const int	half_screen_height = cubed->scene.resol.height / 2;

	i->sprite_height = abs((int)((cubed->scene.resol.height / i->transform_y)
				/ cubed->player.fov_scaling_factor));
	i->sprite_width = i->sprite_height;
	i->draw_start_y = half_screen_height - i->sprite_height / 2;
	i->draw_end_y = half_screen_height + i->sprite_height / 2;
	i->draw_start_x = i->sprite_screen_x - i->sprite_width / 2;
	i->draw_end_x = i->sprite_screen_x + i->sprite_width / 2;
	if (i->draw_start_y < 0)
		i->draw_start_y = 0;
	if (i->draw_end_y >= cubed->scene.resol.height)
		i->draw_end_y = cubed->scene.resol.height - 1;
	if (i->draw_start_x < 0)
		i->draw_start_x = 0;
	if (i->draw_end_x >= cubed->scene.resol.width)
		i->draw_end_x = cubed->scene.resol.width - 1;
	update_health_bar(i, &cubed->scene.resol);
}

void	update_render_info(t_cubed *cubed, double sprite_x, double sprite_y,
		t_sprite_render_info *info)
{
	calculate_transform(cubed, sprite_x, sprite_y, info);
	calculate_draw_boundaries(cubed, info);
}
