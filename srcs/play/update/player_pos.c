/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:03:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/23 14:57:19 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
void	move(t_player *player, double angle, double move_step,
		const t_map *map)
{
	double	new_x;
	double	new_y;
	char	map_char;

	new_x = player->x + cos(angle) * move_step;
	new_y = player->y + sin(angle) * move_step;
	new_x = fmin(fmax(new_x, 0.01), map->width - 0.01);
	new_y = fmin(fmax(new_y, 0.01), map->height - 0.01);
	map_char = t_map_get(map, new_x, new_y);
	if (map_char != '1')
	{
		player->x = new_x;
		player->y = new_y;
		return ;
	}
	map_char = t_map_get(map, player->x, new_y);
	if (map_char != '1')
	{
		player->y = new_y;
		return ;
	}
	map_char = t_map_get(map, new_x, player->y);
	if (map_char != '1')
		player->x = new_x;
}

void	update_player_position(t_player *player, const t_map *map)
{
	if (player->z_move)
	{
		move(player, player->rotation_angle,
			(double)player->z_move
			* player->move_speed, map);
	}
	if (player->x_move)
	{
		move(player, player->rotation_angle + deg2rad(90),
			(double)player->x_move
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
