/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 09:21:49 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare_spawner(t_cubed *cubed, int x, int y)
{
	t_sprite_spawner	*spawner;
	t_sprite_spawner	*new_spawner;

	new_spawner = malloc(sizeof(t_sprite_spawner));
	if (!new_spawner)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC, 0);
	new_spawner->x = x + 0.5;
	new_spawner->y = y + 0.5;
	new_spawner->spawn_interval = 5.0;
	new_spawner->time_since_last_spawn = 0.0;
	new_spawner->health = 100;
	new_spawner->spawner_texture.path = ft_strdup("./assets/sprites/spawner.xpm");
	new_spawner->sprite_texture.path = ft_strdup("./assets/sprites/boggart.xpm");
	if (!new_spawner->spawner_texture.path || !new_spawner->sprite_texture.path)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC, 0);
	load_texture(cubed, cubed->mlx.mlx_ptr, &new_spawner->spawner_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &new_spawner->sprite_texture);
	new_spawner->sprite_texture.is_loaded = true;
	new_spawner->spawner_texture.is_loaded = true;
	new_spawner->next = NULL;
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

	int x, y;
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
