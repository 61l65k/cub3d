/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:55:04 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/17 04:55:08 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_rays(t_game *game)
{
	double ray_angle;
	int i;

	ray_angle = game->player.rotation_angle - game->rays.view_angle / 2;
	i = -1;
	while (++i < game->scene.res.width)
	{
		game->rays.arr[i].angle = ray_angle;
		cast_ray(&game->rays.arr[i], &game->scene.map, &game->player);
		ray_angle += game->rays.view_angle / game->scene.res.width;
	}
}