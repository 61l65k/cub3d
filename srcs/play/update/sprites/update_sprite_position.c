/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:55:16 by ttakala           #+#    #+#             */
/*   Updated: 2024/06/01 16:14:48 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_sprite_position(t_sprite *sprite,
	const t_player *player, t_map *map)
{
	const t_coords	old_pos = {sprite->x, sprite->y};
	const double	distance
		= get_distance(player->x, player->y, old_pos.x, old_pos.y);
	const t_coords	dir = {
		(player->x - old_pos.x) / distance,
		(player->y - old_pos.y) / distance};
	const t_coords	proposed_pos = {
		old_pos.x + dir.x * sprite->speed * SPRITE_SPEED_FACTOR,
		old_pos.y + dir.y * sprite->speed * SPRITE_SPEED_FACTOR};
	const t_coords	new_pos
		= t_map_get_collision_checked_coords_npc(map, proposed_pos, old_pos);

	if (distance < 32)
		t_map_add_ent(map, (t_ent){new_pos, ENT_GENERIC_NPC});
	sprite->x = new_pos.x;
	sprite->y = new_pos.y;
	sprite->distance = distance;
}
