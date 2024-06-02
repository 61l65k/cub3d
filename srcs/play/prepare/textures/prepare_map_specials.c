/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_map_specials.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 19:03:25 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare_spawner(t_cubed *cubed, int x, int y)
{
	t_sprite_spawner	*spawner;
	t_sprite_spawner	*new_spawner;

	new_spawner = ft_calloc(1, sizeof(t_sprite_spawner));
	if (!new_spawner)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC, 0);
	new_spawner->x = x + 0.5;
	new_spawner->y = y + 0.5;
	new_spawner->spawn_interval = 5.0;
	new_spawner->health = SPAWNER_MAX_HEALTH;
	new_spawner->texture = cubed->scene.sprite_info.sprite_texture;
	if (cubed->scene.sprite_info.spawners == NULL)
		cubed->scene.sprite_info.spawners = new_spawner;
	else
	{
		spawner = cubed->scene.sprite_info.spawners;
		while (spawner->next)
			spawner = spawner->next;
		spawner->next = new_spawner;
	}
	cubed->scene.sprite_info.spawner_count++;
}

static void	prepare_door_textures(t_cubed *cubed)
{
	t_sprite_info	*i;
	const char		*closed = "./assets/default/runed_door.xpm";
	const char		*open = "./assets/default/open_door.xpm";

	i = &cubed->scene.sprite_info;
	if (!i->door_open_texture.path || !i->door_closed_texture.path)
	{
		i->door_closed_texture.path = ft_strdup(closed);
		i->door_open_texture.path = ft_strdup(open);
		if (!i->door_open_texture.path || !i->door_closed_texture.path)
			ft_clean_exit(cubed, CUB_ERROR_MALLOC, 0);
	}
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->door_closed_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->door_open_texture);
}

static void	prepare_sprite_boss(t_cubed *cubed, int x, int y)
{
	t_sprite_boss	*new_boss;

	new_boss = ft_calloc(1, sizeof(t_sprite_boss));
	if (!new_boss)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC, 0);
	new_boss->x = x + 0.5;
	new_boss->y = y + 0.5;
	new_boss->speed = 0.2;
	new_boss->distance = 0;
	new_boss->health = BOSS_MAX_HEALTH;
	new_boss->texture = cubed->scene.sprite_info.sprite_boss_texture;
	new_boss->next = cubed->scene.sprite_info.sprite_bosses;
	cubed->scene.sprite_info.sprite_bosses = new_boss;
	cubed->scene.sprite_info.boss_count++;
	t_map_insert(&cubed->scene.map, x, y, '0');
}

static void	prepare_door(t_cubed *cubed, int x, int y)
{
	t_door	*new_door;

	new_door = ft_calloc(1, sizeof(t_door));
	if (!new_door)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC, 0);
	new_door->x = x + 0.5;
	new_door->y = y + 0.5;
	new_door->next = cubed->scene.sprite_info.doors;
	cubed->scene.sprite_info.doors = new_door;
}

void	prepare_map_specials(t_cubed *cubed)
{
	const t_map	*map = &cubed->scene.map;
	int			x;
	int			y;

	cubed->scene.sprite_info.spawner_count = 0;
	y = -1;
	prepare_door_textures(cubed);
	while (++y < (int)map->height)
	{
		x = -1;
		while (++x < (int)map->width)
		{
			if (map->grid[y][x] == 'Z')
				prepare_spawner(cubed, x, y);
			if (map->grid[y][x] == 'D')
				prepare_door(cubed, x, y);
			if (map->grid[y][x] == 'B')
				prepare_sprite_boss(cubed, x, y);
		}
	}
}
