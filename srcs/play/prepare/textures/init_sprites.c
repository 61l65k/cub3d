/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 09:29:54 by apyykone         ###   ########.fr       */
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

void	prepare_sprites(t_cubed *cubed)
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
		}
	}
	if (cubed->scene.sprite_info.spawner_count == 0)
		printf("Warning: No special sprites found!\n");
}
