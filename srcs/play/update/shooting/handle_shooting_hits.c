/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting_hits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:37:14 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 18:10:42 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_damage_to_sprite(t_cubed *cubed, t_sprite *sprite,
		t_sprite *prev_sprite, float damage)
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
		sprite = NULL;
	}
}

static void	apply_damage_to_spawner(t_cubed *cubed, t_sprite_spawner *spawner,
		t_sprite_spawner *prev_spawner, float damage)
{
	spawner->health -= damage;
	if (spawner->health <= 0)
	{
		if (prev_spawner == NULL)
		{
			cubed->scene.sprite_info.spawners = spawner->next;
		}
		else
		{
			prev_spawner->next = spawner->next;
		}
		free_texture(&cubed->mlx, &spawner->spawner_texture);
		free_texture(&cubed->mlx, &spawner->sprite_texture);
		free(spawner);
		spawner = NULL;
	}
}

bool	check_for_hits(t_cubed *cubed, int map_x, int map_y, float damage)
{
	t_sprite			*sprite;
	t_sprite			*prev_sprite;
	t_sprite_spawner	*spawner;
	t_sprite_spawner	*prev_spawner;

	sprite = cubed->scene.sprite_info.sprites;
	prev_sprite = NULL;
	while (sprite)
	{
		if ((int)sprite->x == map_x && (int)sprite->y == map_y)
		{
			apply_damage_to_sprite(cubed, sprite, prev_sprite, damage);
			return (true);
		}
		prev_sprite = sprite;
		sprite = sprite->next;
	}
	spawner = cubed->scene.sprite_info.spawners;
	prev_spawner = NULL;
	while (spawner)
	{
		if ((int)spawner->x == map_x && (int)spawner->y == map_y)
		{
			apply_damage_to_spawner(cubed, spawner, prev_spawner, damage);
			return (true);
		}
		prev_spawner = spawner;
		spawner = spawner->next;
	}
	return (false);
}
