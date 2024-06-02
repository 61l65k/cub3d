/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 14:14:52 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		apply_damage_to_sprite(t_cubed *cubed, t_sprite *sprite,
				t_sprite *prev_sprite, int damage);

static void	handle_gun_shooting(t_cubed *cubed, float damage,
		t_weapon_type weapon_type)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	const t_ray	*middle_ray = &cubed->rays.ray_array[middle_ray_index];
	const int	map_x = (int)middle_ray->x;
	const int	map_y = (int)middle_ray->y;

	if (traverse_and_apply_damage(cubed, middle_ray, 100, damage))
		return ;
	if (weapon_type == WEAPON_RAYGUN
		&& t_map_get(&cubed->scene.map, map_x, map_y) == '1')
	{
		t_map_insert(&cubed->scene.map, map_x, map_y, '0');
	}
}

static void	handle_wrench_shooting(t_cubed *cubed)
{
	const float		distance = 3.0;
	const double	dir[2] = {cubed->player.dir_x * distance,
			cubed->player.dir_y * distance};
	const double	coor[2] = {cubed->player.x + dir[0], cubed->player.y
			+ dir[1]};
	const char		map_char = t_map_get_f(&cubed->scene.map, coor[0], coor[1]);

	if (map_char == '0' || map_char == ' ')
	{
		t_map_insert_f(&cubed->scene.map, coor[0], coor[1], '1');
	}
}

void	handle_shooting(t_cubed *cubed)
{
	const t_weapon_map	*weapon_map = &cubed->weapon_map;
	const int			i = weapon_map->current_weapon;
	const t_weapon		*weapon = &weapon_map->weapons[i];

	if (weapon->type == WEAPON_WRENCH)
	{
		handle_wrench_shooting(cubed);
	}
	else
	{
		handle_gun_shooting(cubed, weapon->damage, weapon->type);
	}
	if (weapon->type != WEAPON_MINIGUN)
	{
		cubed->player.shooting = 0;
	}
}
