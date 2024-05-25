/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 06:00:33 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		load_texture(t_cubed *cubed, void *mlx, t_texture *texture);

static void	prepare_spawner(t_cubed *cubed, int x, int y)
{
	t_sprite_spawner	*spawner;
	const size_t		old_size = sizeof(t_sprite_spawner)
				* cubed->scene.sprite_info.spawner_count;
	const size_t		new_size = sizeof(t_sprite_spawner)
				* (cubed->scene.sprite_info.spawner_count + 1);

	cubed->scene.sprite_info.spawners = ft_realloc(cubed->scene.sprite_info.spawners,
			old_size, new_size);
	if (!cubed->scene.sprite_info.spawners)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC);
	spawner = &cubed->scene.sprite_info.spawners[cubed->scene.sprite_info.spawner_count];
	spawner->x = x + 0.5;
	spawner->y = y + 0.5;
	spawner->spawn_interval = 5.0; // Create some random time interval
	spawner->time_since_last_spawn = 0.0;
	spawner->texture.path = ft_strdup("./assets/sprites/spawner.xpm");
	if (!spawner->texture.path)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC);
	load_texture(cubed, cubed->mlx.mlx_ptr, &spawner->texture);
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
