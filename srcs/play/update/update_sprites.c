/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:50:19 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 03:35:02 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_transform(t_cubed *cubed, double sprite_x, double sprite_y,
		t_sprite_render_info *transform)
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

void	calculate_draw_boundaries(t_cubed *cubed,
		t_sprite_render_info *transform)
{
	transform->sprite_height = abs((int)(cubed->scene.resol.height
				/ transform->transform_y));
	transform->sprite_width = transform->sprite_height;
	transform->draw_start_y = -transform->sprite_height / 2
		+ cubed->scene.resol.height / 2;
	if (transform->draw_start_y < 0)
		transform->draw_start_y = 0;
	transform->draw_end_y = transform->sprite_height / 2
		+ cubed->scene.resol.height / 2;
	if (transform->draw_end_y >= cubed->scene.resol.height)
		transform->draw_end_y = cubed->scene.resol.height - 1;
	transform->draw_start_x = -transform->sprite_width / 2
		+ transform->sprite_screen_x;
	if (transform->draw_start_x < 0)
		transform->draw_start_x = 0;
	transform->draw_end_x = transform->sprite_width / 2
		+ transform->sprite_screen_x;
	if (transform->draw_end_x >= cubed->scene.resol.width)
		transform->draw_end_x = cubed->scene.resol.width - 1;
}

void	update_render_info(t_cubed *cubed, double sprite_x, double sprite_y,
		t_sprite_render_info *transform)
{
	calculate_transform(cubed, sprite_x, sprite_y, transform);
	calculate_draw_boundaries(cubed, transform);
}

void	update_sprite_render_info(t_cubed *cubed)
{
	t_sprite_spawner	*spawner;
	int					i;

	// t_sprite			*sprite;
	i = -1;
	while (++i < cubed->scene.sprite_info.spawner_count)
	{
		spawner = &cubed->scene.sprite_info.spawners[i];
		update_render_info(cubed, spawner->x, spawner->y, &spawner->info);
	}
}
