/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:03:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/18 03:41:44 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_position(t_player *player, char **map)
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
	if (!ft_strchr("12", map[(int)new_y][(int)new_x]))
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
