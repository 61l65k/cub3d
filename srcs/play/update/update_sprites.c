/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:50:19 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 06:42:19 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	spawn_sprites(t_cubed *cubed, t_sprite_spawner *spawner)
{
	t_sprite	*new_sprite;

	spawner->time_since_last_spawn += 0.0005;
	if (spawner->time_since_last_spawn >= spawner->spawn_interval)
	{
		new_sprite = malloc(sizeof(t_sprite));
		if (!new_sprite)
			ft_clean_exit(cubed, "Failed to allocate memory for new sprite");
		new_sprite->x = spawner->x;
		new_sprite->y = spawner->y;
		new_sprite->texture = spawner->texture;
		new_sprite->speed = 0.01;
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

	double direction_x, direction_y, distance;
	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		direction_x = cubed->player.x - sprite->x;
		direction_y = cubed->player.y - sprite->y;
		distance = sqrt(direction_x * direction_x + direction_y * direction_y);
		if (distance > 0)
		{
			direction_x /= distance;
			direction_y /= distance;
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
