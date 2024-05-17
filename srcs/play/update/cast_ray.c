/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:55:04 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/17 11:11:24 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "cub3d.h"
// t_game type not defined
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
*/