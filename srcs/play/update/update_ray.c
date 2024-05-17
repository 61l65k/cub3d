/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:53:08 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/18 02:06:55 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_rays(t_cubed *game)
{
	double	ray_angle;
	int		i;

	ray_angle = game->player.rotation_angle - game->rays.view_angle / 2;
	i = -1;
	while (++i < game->scene.resolution.width)
	{
		game->rays.ray_array[i].angle = ray_angle;
		// cast_ray(&game->rays.ray_array[i], &game->scene.map, &game->player);
		ray_angle += game->rays.view_angle / game->scene.resolution.width;
	}
}

void	update_rays_hard(t_cubed *game)
{
	double	ray_angle;
	int		i;

	ray_angle = game->player.rotation_angle - game->rays.view_angle / 2;
	i = -1;
	while (++i < game->scene.resolution.width)
	{
		game->rays.ray_array[i].angle = ray_angle;
		game->rays.ray_array[i].size = 1.0 / ((i + 1)
				/ (double)game->scene.resolution.width);
		game->rays.ray_array[i].orientation = 'N';
		game->rays.ray_array[i].x = game->player.x + cos(ray_angle)
			* game->rays.ray_array[i].size;
		game->rays.ray_array[i].y = game->player.y + sin(ray_angle)
			* game->rays.ray_array[i].size;
		ray_angle += game->rays.view_angle / game->scene.resolution.width;
	}
}
