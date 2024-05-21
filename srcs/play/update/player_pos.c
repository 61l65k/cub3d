/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:03:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/21 20:01:22 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	player_coordinates_are_within_bounds(double x, double y,
		const t_map *t_map)
{
	if (x < 0 || y < 0 || y >= t_map->height || x >= t_map->width)
	{
		// printf("Player out of bounds: x=%f map_w=%lu, y=%f map_h=%lu\n", x,
		//		t_map->width, y, t_map->height);
		return (0);
	}
	return (1);
}

static void	move(t_player *player, double angle, double move_step,
		const t_map *map)
{
	const double	new_x = player->x + cos(angle) * move_step;
	const double	new_y = player->y + sin(angle) * move_step;

	if (player_coordinates_are_within_bounds(new_x, new_y, map)
		&& !ft_strchr("12", map->grid[(int)new_y][(int)new_x]))
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
