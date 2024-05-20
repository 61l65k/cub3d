/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:53:08 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 17:31:01 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_rays(t_cubed *cubed)
{
	double	ray_angle;
	int		i;

	ray_angle = cubed->player.rotation_angle - cubed->rays.view_angle / 2;
	i = -1;
	while (++i < cubed->scene.resolution.width)
	{
		cubed->rays.ray_array[i].angle = ray_angle;
		cast_ray(&cubed->rays.ray_array[i], &cubed->scene.map, &cubed->player);
		ray_angle += cubed->rays.view_angle / cubed->scene.resolution.width;
	}
}
