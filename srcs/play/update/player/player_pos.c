/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:03:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 17:52:34 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move(t_player *player, double angle, double move_step,
		const t_map *map)
{
	t_coords	new;

	new.x = player->x + cos(angle) * move_step;
	new.y = player->y + sin(angle) * move_step;
	new = t_map_get_collision_checked_coords(map, new,
			(t_coords){player->x, player->y});
	player->x = new.x;
	player->y = new.y;
}

void	update_player_position(t_player *player, const t_map *map)
{
	if (player->z_move)
	{
		move(player, player->rotation_angle, (double)player->z_move
			* player->move_speed, map);
	}
	if (player->x_move)
	{
		move(player, player->rotation_angle + deg2rad(90),
			(double)player->x_move * player->move_speed, map);
	}
}

void	update_player_orientation(t_player *player)
{
	if (player->turn_direction != 0)
	{
		player->rotation_angle += player->turn_direction
			* player->rotation_speed;
	}
	player->dir_x = cos(player->rotation_angle);
	player->dir_y = sin(player->rotation_angle);
	player->plane_x = -player->dir_y * player->fov_rad / 2;
	player->plane_y = player->dir_x * player->fov_rad / 2;
}
