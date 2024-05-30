/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:55:16 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/30 22:28:14 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_coords	get_direction(const t_sprite *sprite, const t_player *player,
	double distance)
{
	t_coords	dir;

	if (distance > 0)
	{
		dir.x = (player->x - sprite->x) / distance;
		dir.y = (player->y - sprite->y) / distance;
	}
	else
	{
		dir.x = (player->x - sprite->x);
		dir.y = (player->y - sprite->y);
	}
	return (dir);
}

void	update_sprite_position(t_sprite *sprite,
	const t_player *player, t_map *map)
{
	const t_coords	old_pos = {sprite->x, sprite->y};
	const double	distance
		= get_distance(player->x, player->y, old_pos.x, old_pos.y);
	const t_coords	dir = get_direction(sprite, player, distance);
	const t_coords	proposed_pos = {
		sprite->x + dir.x * sprite->speed * SPRITE_SPEED_FACTOR,
		sprite->y + dir.y * sprite->speed * SPRITE_SPEED_FACTOR};
	const t_coords	new_pos
		= t_map_get_collision_checked_coords(map, proposed_pos, old_pos);

	t_map_add_entity(map, (t_ent){new_pos, ENT_GENERIC});
	sprite->x = new_pos.x;
	sprite->y = new_pos.y;
	sprite->distance = distance;
}
