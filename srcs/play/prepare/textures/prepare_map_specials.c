/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_map_specials.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/29 11:40:51 by apyykone         ###   ########.fr       */
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
	new_spawner->health = 100;
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
	if (!cubed->scene.sprite_info.door_open_texture.path
		|| !cubed->scene.sprite_info.door_closed_texture.path)
	{
		cubed->scene.sprite_info.door_closed_texture.path = ft_strdup("./assets/sprites/runed_door.xpm");
		if (!cubed->scene.sprite_info.door_closed_texture.path)
			ft_clean_exit(cubed, CUB_ERROR_MALLOC, 0);
		cubed->scene.sprite_info.door_open_texture.path = ft_strdup("./assets/sprites/open_door.xpm");
	}
	load_texture(cubed, cubed->mlx.mlx_ptr,
		&cubed->scene.sprite_info.door_closed_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr,
		&cubed->scene.sprite_info.door_open_texture);
}

void	prepare_map_specials(t_cubed *cubed)
{
	const t_map	*map = &cubed->scene.map;
	int			x;
	int			y;

	cubed->scene.sprite_info.spawner_count = 0;
	y = -1;
	while (++y < (int)map->height)
	{
		x = -1;
		while (++x < (int)map->width)
		{
			if (map->grid[y][x] == 'Z')
			{
				prepare_spawner(cubed, x, y);
			}
			if (map->grid[y][x] == 'D')
			{
				prepare_door(cubed, x, y);
			}
		}
	}
}
