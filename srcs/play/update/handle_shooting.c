/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 14:23:50 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_shooting(t_cubed *cubed)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	t_ray		*middle_ray;
	int			map_x;
	int			map_y;

	middle_ray = &cubed->rays.ray_array[middle_ray_index];
	map_x = (int)middle_ray->x;
	map_y = (int)middle_ray->y;
	if (t_map_get(&cubed->scene.map, map_x, map_y) == '1')
	{
		t_map_insert(&cubed->scene.map, map_x, map_y, '0');
	}
}
