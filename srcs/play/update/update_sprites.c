/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:50:19 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 11:35:19 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_damage_to_sprite(t_cubed *cubed, t_sprite *sprite,
		t_sprite *prev_sprite, int damage)
{
	sprite->health -= damage;
	if (sprite->health <= 0)
	{
		if (prev_sprite == NULL)
		{
			cubed->scene.sprite_info.sprites = sprite->next;
		}
		else
		{
			prev_sprite->next = sprite->next;
		}
		free(sprite);
	}
}

static void	spawn_sprites(t_cubed *cubed, t_sprite_spawner *spawner)
{
	t_sprite	*new_sprite;

	spawner->time_since_last_spawn += 0.001;
	if (spawner->time_since_last_spawn >= spawner->spawn_interval)
	{
		new_sprite = create_sprite_node(cubed, spawner->x, spawner->y,
				&spawner->sprite_texture);
		new_sprite->next = cubed->scene.sprite_info.sprites;
		cubed->scene.sprite_info.sprites = new_sprite;
		spawner->time_since_last_spawn = 0;
		spawner->spawn_interval = (rand() % 10) + 5;
	}
}

static void	update_spawners(t_cubed *cubed)
{
	t_sprite_spawner	*spawner;
	int					i;

	i = -1;
	while (++i < cubed->scene.sprite_info.spawner_count)
	{
		spawner = &cubed->scene.sprite_info.spawners[i];
		update_render_info(cubed, spawner->x, spawner->y, &spawner->info);
		spawn_sprites(cubed, spawner);
	}
}

static void	update_all_sprites(t_cubed *cubed)
{
	t_sprite	*sprite;

	double direction_x, direction_y;
	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		direction_x = cubed->player.x - sprite->x;
		direction_y = cubed->player.y - sprite->y;
		sprite->distance = sqrt(direction_x * direction_x + direction_y
				* direction_y);
		if (sprite->distance > 0)
		{
			direction_x /= sprite->distance;
			direction_y /= sprite->distance;
		}
		sprite->x += direction_x * sprite->speed * SPRITE_SPEED_FACTOR;
		sprite->y += direction_y * sprite->speed * SPRITE_SPEED_FACTOR;
		update_render_info(cubed, sprite->x, sprite->y, &sprite->info);
		sprite = sprite->next;
	}
}

void	update_sprite_render_info(t_cubed *cubed)
{
	update_spawners(cubed);
	update_all_sprites(cubed);
}
