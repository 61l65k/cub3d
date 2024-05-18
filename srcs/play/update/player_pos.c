/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:03:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/18 14:03:08 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int player_coordinates_are_within_bounds(double x, double y, const t_map *t_map)
{
	if (x < 0 || y < 0 || y >= t_map->height || x >= t_map->width)
	{
		printf("Player out of bounds: x=%f map_w=%lu, y=%f map_h=%lu\n",
			x, t_map->width, y, t_map->height);
		return (0);
	}
	return (1);
}

void	update_player_position(t_player *player, const t_map *t_map)
{
	double	move_step;
	double	new_x;
	double	new_y;

	if (player->walk_direction == 0)
		return ;
	move_step = player->move_speed * (player->walk_direction == 's' ? -1 : 1);
	new_x = player->x + cos(player->rotation_angle) * move_step;
	new_y = player->y + sin(player->rotation_angle) * move_step;
	if (player->walk_direction == 'a' || player->walk_direction == 'd')
	{
		move_step = player->move_speed * (player->walk_direction == 'a' ?
				-1 : 1);
		new_x = player->x + cos(player->rotation_angle + degree_to_radian(90))
			* move_step;
		new_y = player->y + sin(player->rotation_angle + degree_to_radian(90))
			* move_step;
	}
	if (!player_coordinates_are_within_bounds(new_x, new_y, t_map))
		return ;
	if (!ft_strchr("12", t_map->grid[(int)new_y][(int)new_x]))
	{
		player->x = new_x;
		player->y = new_y;
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
