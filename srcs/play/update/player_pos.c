/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:03:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 12:20:44 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move(t_player *player, double angle, double move_step,
		const t_map *map)
{
	const double	new_x = player->x + cos(angle) * move_step;
	const double	new_y = player->y + sin(angle) * move_step;
	const char		map_val = t_map_get(map, (int)new_x, (int)new_y);

	if (map_val != '\0' && map_val != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
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
		move(player, player->rotation_angle + deg2rad(90), (double)player->x_move
			* player->move_speed, map);
	}
}

void	update_player_orientation(t_player *player)
{
	if (player->turn_direction != 0)
	{
		player->rotation_angle += player->turn_direction
			* player->rotation_speed;
	}
}
