/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:55:16 by ttakala           #+#    #+#             */
/*   Updated: 2024/06/03 00:06:54 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coords	apply_special_effects(t_coords dir, t_sprite *sprite,
		const t_item_effects *effects)
{
	if (effects->cloak_effect_timer > 0)
	{
		dir.x = -dir.x;
		dir.y = -dir.y;
	}
	if (effects->slowdown_effect_timer > 0)
	{
		sprite->speed *= effects->slowdown_factor;
	}
	return (dir);
}

void	update_sprite_position(t_sprite *sprite, const t_player *player,
		t_map *map)
{
	const t_coords	old_pos = {sprite->x, sprite->y};
	const double	distance
		= get_distance(player->x, player->y, old_pos.x, old_pos.y);
	const t_coords	dir
		= apply_special_effects(((t_coords){(player->x - old_pos.x) / distance,
				(player->y - old_pos.y) / distance}), (t_sprite *)sprite,
			&player->effects);
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

void	update_boss_position(t_sprite_boss *boss, const t_player *player,
		t_map *map)
{
	const t_coords	old_pos = {boss->x, boss->y};
	const double	distance
		= get_distance(player->x, player->y, old_pos.x, old_pos.y);
	const t_coords	dir
		= apply_special_effects(((t_coords){(player->x - old_pos.x) / distance,
				(player->y - old_pos.y) / distance}),
			(t_sprite *)boss, &player->effects);
	const t_coords	proposed_pos = {
		old_pos.x + dir.x * boss->speed * BOSS_SPEED_FACTOR,
		old_pos.y + dir.y * boss->speed * BOSS_SPEED_FACTOR};
	const t_coords	new_pos
		= t_map_get_collision_checked_coords_npc(map, proposed_pos, old_pos);

	if (distance < 32)
		t_map_add_ent(map, (t_ent){new_pos, ENT_GENERIC_NPC});
	boss->x = new_pos.x;
	boss->y = new_pos.y;
	boss->distance = distance;
}
