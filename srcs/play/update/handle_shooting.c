/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/23 15:21:05 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_akimbos_shooting(t_cubed *cubed)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	const t_ray	*middle_ray = &cubed->rays.ray_array[middle_ray_index];
	const int	map_x = (int)middle_ray->x;
	const int	map_y = (int)middle_ray->y;

	if (t_map_get(&cubed->scene.map, map_x, map_y) == '1')
	{
		t_map_insert(&cubed->scene.map, map_x, map_y, '0');
	}
}

static void	handle_wrench_shooting(t_cubed *cubed)
{
	const int	map_x = (int)(cubed->player.x);
	const int	map_y = (int)(cubed->player.y + 1);

	if (t_map_get(&cubed->scene.map, map_x, map_y) == '0')
	{
		t_map_insert(&cubed->scene.map, map_x, map_y, '1');
	}
}

static void	handle_raygun_shooting(t_cubed *cubed)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	const t_ray	*middle_ray = &cubed->rays.ray_array[middle_ray_index];
	const int	map_x = (int)middle_ray->x;
	const int	map_y = (int)middle_ray->y;
	int			dx;
	int			dy;
	int			adj_map_x;
	int			adj_map_y;

	dx = -1;
	while (dx <= 1)
	{
		dy = -1;
		while (dy <= 1)
		{
			if (dx || dy)
			{
				adj_map_x = map_x + dx;
				adj_map_y = map_y + dy;
				if (t_map_get(&cubed->scene.map, adj_map_x, adj_map_y) == '1')
				{
					t_map_insert(&cubed->scene.map, adj_map_x, adj_map_y, '0');
				}
			}
			dy++;
		}
		dx++;
	}
}

void	handle_shooting(t_cubed *cubed)
{
	t_weapon_map	*weapon_map;
	t_weapon		*current_weapon;

	weapon_map = &cubed->scene.weapon_map;
	current_weapon = &weapon_map->weapons[weapon_map->current_weapon];
	printf("Shooting with weapon %d\n", current_weapon->type);
	if (current_weapon->type == WEAPON_AKIMBOS)
	{
		handle_akimbos_shooting(cubed);
	}
	else if (current_weapon->type == WEAPON_WRENCH)
	{
		handle_wrench_shooting(cubed);
	}
	else if (current_weapon->type == WEAPON_RAYGUN)
	{
		handle_akimbos_shooting(cubed);
	}
	else
		handle_raygun_shooting(cubed);
}
