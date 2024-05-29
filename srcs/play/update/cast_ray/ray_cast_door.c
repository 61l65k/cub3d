/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:57:24 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/29 11:44:40 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*find_door(t_cubed *cubed, int map_x, int map_y)
{
	t_door	*door;

	door = cubed->scene.sprite_info.doors;
	while (door)
	{
		if ((int)door->x == map_x && (int)door->y == map_y)
			return (door);
		door = door->next;
	}
	return (NULL);
}

int	ray_check_door(t_cubed *cubed, t_ray *ray, int i, double *ray_angle)
{
	const double	door_open_distance = 3;
	const char		c = t_map_get_f(&cubed->scene.map, ray->x, ray->y);
	t_door			*door;

	if (c == 'D')
	{
		door = find_door(cubed, ray->x, ray->y);
		if (door)
		{
			ray->orientation = 'D';
			ray->is_door = true;
			ray->door = door;
			cubed->rays.ray_array[i] = *ray;
			*ray_angle += cubed->rays.field_of_view / cubed->scene.resol.width;
			door->is_open = (get_distance(cubed->player.x, cubed->player.y,
						door->x, door->y) < door_open_distance);
			if (door->is_open)
				ray->orientation = 0;
			return (DOOR_FOUND);
		}
	}
	ray->is_door = false;
	return (DOOR_NOT_FOUND);
}
