/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting_hits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:37:14 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 19:49:35 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	hit_sprite(t_cubed *cubed, t_sprite *sprite, t_sprite *prev_sprite,
		float damage)
{
	sprite->health -= damage;
	if (sprite->health <= 0)
	{
		if (prev_sprite == NULL)
			cubed->scene.sprite_info.sprites = sprite->next;
		else
			prev_sprite->next = sprite->next;
		free(sprite);
		sprite = NULL;
	}
	else
		sprite->info.health_bar.health_percentage = sprite->health
			/ SPRITE_MAX_HEALTH;
	return (true);
}

static bool	hit_spawner(t_cubed *cubed, t_sprite_spawner *spawner,
		t_sprite_spawner *prev_spawner, float damage)
{
	spawner->health -= damage;
	if (spawner->health <= 0)
	{
		t_map_insert_f(&cubed->scene.map, spawner->x, spawner->y, '0');
		if (prev_spawner == NULL)
			cubed->scene.sprite_info.spawners = spawner->next;
		else
			prev_spawner->next = spawner->next;
		free(spawner);
	}
	else
		spawner->info.health_bar.health_percentage = spawner->health
			/ SPAWNER_MAX_HEALTH;
	return (true);
}

static bool	hit_boss(t_cubed *cubed, t_sprite_boss *boss,
		t_sprite_boss *prev_boss, float damage)
{
	boss->health -= damage;
	if (boss->health <= 0)
	{
		if (prev_boss == NULL)
			cubed->scene.sprite_info.sprite_bosses = boss->next;
		else
			prev_boss->next = boss->next;
		free(boss);
		boss = NULL;
	}
	else
		boss->info.health_bar.health_percentage = boss->health
			/ BOSS_MAX_HEALTH;
	return (true);
}

static bool	check_boss_sprite_hit(t_cubed *cubed, int map_x, int map_y,
		float damage)
{
	t_sprite_boss	*boss;
	t_sprite_boss	*prev_boss;
	t_sprite		*sprite;
	t_sprite		*prev_sprite;

	sprite = cubed->scene.sprite_info.sprites;
	prev_sprite = NULL;
	while (sprite)
	{
		if ((int)sprite->x == map_x && (int)sprite->y == map_y)
			return (hit_sprite(cubed, sprite, prev_sprite, damage));
		prev_sprite = sprite;
		sprite = sprite->next;
	}
	boss = cubed->scene.sprite_info.sprite_bosses;
	prev_boss = NULL;
	while (boss)
	{
		if ((int)boss->x == map_x && (int)boss->y == map_y)
			return (hit_boss(cubed, boss, prev_boss, damage));
		prev_boss = boss;
		boss = boss->next;
	}
	return (false);
}

bool	check_for_hits(t_cubed *cubed, int map_x, int map_y, float damage)
{
	t_sprite_spawner	*spawner;
	t_sprite_spawner	*prev_spawner;

	if (check_boss_sprite_hit(cubed, map_x, map_y, damage))
		return (true);
	spawner = cubed->scene.sprite_info.spawners;
	prev_spawner = NULL;
	while (spawner)
	{
		if ((int)spawner->x == map_x && (int)spawner->y == map_y)
			return (hit_spawner(cubed, spawner, prev_spawner, damage));
		prev_spawner = spawner;
		spawner = spawner->next;
	}
	return (false);
}
