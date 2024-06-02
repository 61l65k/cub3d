/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_renderables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:52:03 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 18:35:44 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "renderable.h"

t_renderable	*collect_wall_renderables(t_cubed *cubed,
		t_renderable *renderables, int *idx)
{
	int		i;
	t_ray	*ray;

	i = 0;
	while (i < cubed->rays.ray_count)
	{
		ray = &cubed->rays.ray_array[i];
		renderables[*idx].distance = ray->distance;
		renderables[*idx].type = RENDERABLE_WALL;
		renderables[*idx].data.ray = ray;
		(*idx)++;
		i++;
	}
	return (renderables);
}

t_renderable	*collect_spawner_and_item_renderables(t_cubed *cubed,
		t_renderable *renderables, int *idx)
{
	t_sprite_spawner	*spawner;
	t_item				*item;

	spawner = cubed->scene.sprite_info.spawners;
	while (spawner)
	{
		renderables[*idx].distance = spawner->distance;
		renderables[*idx].type = RENDERABLE_SPAWNER;
		renderables[*idx].data.spawner = spawner;
		(*idx)++;
		spawner = spawner->next;
	}
	item = cubed->scene.sprite_info.item_info.items;
	while (item)
	{
		renderables[*idx].distance = item->distance;
		renderables[*idx].type = RENDERABLE_ITEM;
		renderables[*idx].data.item = item;
		(*idx)++;
		item = item->next;
	}
	return (renderables);
}

t_renderable	*collect_sprite_and_boss_renderables(t_cubed *cubed,
		t_renderable *renderables, int *idx)
{
	t_sprite		*sprite;
	t_sprite_boss	*boss;

	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		renderables[*idx].distance = sprite->distance;
		renderables[*idx].type = RENDERABLE_SPRITE;
		renderables[*idx].data.sprite = sprite;
		(*idx)++;
		sprite = sprite->next;
	}
	boss = cubed->scene.sprite_info.sprite_bosses;
	while (boss)
	{
		renderables[*idx].distance = boss->distance;
		renderables[*idx].type = RENDERABLE_BOSS;
		renderables[*idx].data.boss = boss;
		(*idx)++;
		boss = boss->next;
	}
	return (renderables);
}

static int	calculate_total_renderables(t_cubed *cubed)
{
	return (cubed->rays.ray_count + cubed->scene.sprite_info.spawner_count
		+ cubed->scene.sprite_info.sprites_count
		+ cubed->scene.sprite_info.door_count
		+ cubed->scene.sprite_info.boss_count
		+ cubed->scene.sprite_info.item_info.item_count);
}

t_renderable	*collect_renderables(t_cubed *cubed, int *count)
{
	const int		total_count = calculate_total_renderables(cubed);
	t_renderable	*renderables;
	int				idx;

	renderables = malloc(total_count * sizeof(t_renderable));
	if (!renderables)
		ft_clean_exit(cubed, ERR_ALLOC_RENDERABLES, 0);
	idx = 0;
	renderables = collect_wall_renderables(cubed, renderables, &idx);
	renderables = collect_spawner_and_item_renderables(cubed, renderables,
			&idx);
	renderables = collect_sprite_and_boss_renderables(cubed, renderables, &idx);
	*count = idx;
	return (renderables);
}
