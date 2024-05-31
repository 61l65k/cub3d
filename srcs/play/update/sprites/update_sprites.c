/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:50:19 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 19:58:34 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*create_sprite_node(t_cubed *cubed, double x, double y,
		t_texture *texture)
{
	t_sprite	*new_sprite;

	new_sprite = ft_calloc(1, sizeof(t_sprite));
	if (!new_sprite)
		ft_clean_exit(cubed, ERR_SPRITE_ALLOC, 0);
	new_sprite->x = x;
	new_sprite->y = y;
	cubed->scene.sprite_info.sprites_count++;
	new_sprite->texture = *texture;
	new_sprite->speed = 0.2;
	if (!LINUX)
		new_sprite->speed = 0.4;
	new_sprite->health = SPRITE_MAX_HEALTH;
	return (new_sprite);
}

static void	spawn_sprites(t_cubed *cubed, t_sprite_spawner *spawner)
{
	t_sprite	*new_sprite;

	spawner->time_since_last_spawn += 0.005;
	if (spawner->time_since_last_spawn >= spawner->spawn_interval)
	{
		new_sprite = create_sprite_node(cubed, spawner->x, spawner->y,
				&cubed->scene.sprite_info.sprite_texture);
		new_sprite->next = cubed->scene.sprite_info.sprites;
		cubed->scene.sprite_info.sprites = new_sprite;
		spawner->time_since_last_spawn = 0;
		spawner->spawn_interval = 10;
	}
}

static void	update_spawners(t_cubed *cubed)
{
	t_sprite_spawner	*spawner;

	spawner = cubed->scene.sprite_info.spawners;
	while (spawner)
	{
		spawner->distance = get_distance(cubed->player.x, cubed->player.y,
				spawner->x, spawner->y);
		update_render_info(cubed, spawner->x, spawner->y, &spawner->info);
		spawn_sprites(cubed, spawner);
		spawner = spawner->next;
	}
}

void		update_sprite_position(t_sprite *sprite, const t_player *player,
				t_map *map);

static void	update_all_sprites(t_cubed *cubed)
{
	t_sprite	*spr;

	spr = cubed->scene.sprite_info.sprites;
	while (spr)
	{
		update_sprite_position(spr, &cubed->player, &cubed->scene.map);
		update_render_info(cubed, spr->x, spr->y, &spr->info);
		check_sprite_hit_player(cubed, spr);
		spr = spr->next;
	}
}

void	update_sprite_render_info(t_cubed *cubed)
{
	t_door	*door;

	update_spawners(cubed);
	update_all_sprites(cubed);
	door = cubed->scene.sprite_info.doors;
	while (door)
	{
		door->distance = get_distance(cubed->player.x, cubed->player.y, door->x,
				door->y);
		door = door->next;
	}
}
