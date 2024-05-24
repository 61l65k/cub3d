/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 01:10:47 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		load_texture(t_cubed *cubed, void *mlx, t_texture *texture);

static void	prepare_spawners(t_cubed *cubed)
{
	const t_map			*map = &cubed->scene.map;
	t_sprite_spawner	*spawner;
	int					x;
	int					y;

	cubed->scene.sprite_info.spawner_count = 0;
	y = -1;
	while (++y < (int)map->height)
	{
		x = -1;
		while (++x < (int)map->width)
		{
			if (map->grid[y][x] == 'Z')
			{
				cubed->scene.sprite_info.spawners = realloc(cubed->scene.sprite_info.spawners,
						sizeof(t_sprite_spawner)
						* (cubed->scene.sprite_info.spawner_count + 1));
				if (!cubed->scene.sprite_info.spawners)
					ft_clean_exit(cubed, CUB_ERROR_MALLOC);
				spawner = &cubed->scene.sprite_info.spawners[cubed->scene.sprite_info.spawner_count];
				spawner->x = x + 0.5;
				spawner->y = y + 0.5;
				spawner->texture.path = ft_strdup("./assets/sprites/spawner.xpm");
				if (!spawner->texture.path)
					ft_clean_exit(cubed, CUB_ERROR_MALLOC);
				printf("spawned count: %d\n",
					cubed->scene.sprite_info.spawner_count);
				printf("PATH:  %s\n", spawner->texture.path);
				if (cubed->mlx.mlx_ptr == NULL)
					ft_clean_exit(cubed, "MLX pointer is NULL");
				load_texture(cubed, cubed->mlx.mlx_ptr, &spawner->texture);
				cubed->scene.sprite_info.spawner_count++;
			}
		}
	}
	if (cubed->scene.sprite_info.spawner_count == 0)
		printf("Warning: No spawners found in the map\n");
}

void	prepare_sprites(t_cubed *cubed)
{
	prepare_spawners(cubed);
}