/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 09:24:49 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_shooting(t_cubed *cubed)
{
	const int	middle_ray_index = cubed->scene.resolution.width / 2;
	t_ray		*middle_ray;
	int			map_x;
	int			map_y;

	middle_ray = &cubed->rays.ray_array[middle_ray_index];
	map_x = (int)middle_ray->x;
	map_y = (int)middle_ray->y;
	if (map_x >= 0 && map_x < (int)cubed->scene.map.width && map_y >= 0
		&& map_y < (int)cubed->scene.map.height)
	{
		if (cubed->scene.map.grid[map_y][map_x] == '1')
		{
			cubed->scene.map.grid[map_y][map_x] = '0';
			middle_ray->obstacle = '0';
		}
	}
}
