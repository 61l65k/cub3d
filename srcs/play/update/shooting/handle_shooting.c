/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/27 20:37:45 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		apply_damage_to_sprite(t_cubed *cubed, t_sprite *sprite,
				t_sprite *prev_sprite, int damage);

static void	handle_gun_shooting(t_cubed *cubed, float damage)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	const t_ray	*middle_ray = &cubed->rays.ray_array[middle_ray_index];
	const int	map_x = (int)middle_ray->x;
	const int	map_y = (int)middle_ray->y;

	if (traverse_and_apply_damage(cubed, middle_ray, 100, damage))
		return ;
	if (t_map_get(&cubed->scene.map, map_x, map_y) == '1')
	{
		t_map_insert(&cubed->scene.map, map_x, map_y, '0');
	}
}

static void	handle_wrench_shooting(t_cubed *cubed)
{
	const float	distance = 3.0;
	const double dir[2] = {cubed->player.dir_x * distance,
		cubed->player.dir_y * distance};
	const double coor[2] = {cubed->player.x + dir[0], cubed->player.y + dir[1]};
	const char	map_char = t_map_get_f(&cubed->scene.map, coor[0], coor[1]);

	if (map_char == '0' || map_char == ' ')
		t_map_insert_f(&cubed->scene.map, coor[0], coor[1], '1');
}

static void	destroy_adjacent_walls(t_cubed *cubed, int map_x, int map_y,
		int depth)
{
	int	dx;
	int	dy;

	if (depth == 4 || t_map_get(&cubed->scene.map, map_x, map_y) != '1')
		return ;
	t_map_insert(&cubed->scene.map, map_x, map_y, '0');
	depth = depth + 1;
	dx = -2;
	while (++dx <= 1)
	{
		dy = -2;
		while (++dy <= 1)
		{
			if (dx != 0 || dy != 0)
				destroy_adjacent_walls(cubed, map_x + dx, map_y + dy, depth);
		}
	}
}

static void	handle_raygun_shooting(t_cubed *cubed)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	const t_ray	*middle_ray = &cubed->rays.ray_array[middle_ray_index];
	const int	map_x = (int)middle_ray->x;
	const int	map_y = (int)middle_ray->y;

	if (traverse_and_apply_damage(cubed, middle_ray, 100, 10))
		return ;
	if (t_map_get(&cubed->scene.map, map_x, map_y) == '1')
		destroy_adjacent_walls(cubed, map_x, map_y, 0);
}

void	handle_shooting(t_cubed *cubed)
{
	const t_weapon_map	*weapon_map = &cubed->weapon_map;
	const t_weapon		*current_weapon = &weapon_map->weapons[weapon_map->current_weapon];

	if (current_weapon->type == WEAPON_AKIMBOS)
	{
		handle_gun_shooting(cubed, 10);
	}
	else if (current_weapon->type == WEAPON_WRENCH)
	{
		handle_wrench_shooting(cubed);
	}
	else if (current_weapon->type == WEAPON_RAYGUN)
	{
		handle_raygun_shooting(cubed);
	}
	else if (current_weapon->type == WEAPON_MINIGUN)
	{
		handle_gun_shooting(cubed, 0.1);
	}
	if (current_weapon->type != WEAPON_MINIGUN)
	{
		cubed->player.shooting = 0;
	}
}
