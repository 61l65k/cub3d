/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:58:18 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 14:21:02 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_resolution(t_resolution *resolution)
{
	if (resolution->width == 0 || resolution->height == 0)
	{
		printf("No resolution found from .cub file\n");
		printf("Defaulting to %s\n", RES_DEFAULT_STR);
		resolution->width = RES_DEFAULT_W;
		resolution->height = RES_DEFAULT_H;
	}
	else if (resolution->width > RES_MAX_W || resolution->height > RES_MAX_H)
	{
		printf("Resolution in .cub file is too high\n");
		printf("Defaulting to the maximum %s\n", RES_MAX_STR);
		resolution->width = RES_MAX_W;
		resolution->height = RES_MAX_H;
	}
	else if (resolution->width < RES_MIN_W || resolution->height < RES_MIN_H)
	{
		printf("Resolution in .cub file is too low\n");
		printf("Defaulting to the minimum %s\n", RES_MIN_STR);
		resolution->width = RES_MIN_W;
		resolution->height = RES_MIN_H;
	}
}

static void	validate_textures(t_cubed *cubed)
{
	const t_scenedata	*scene = &cubed->scene;

	if (!does_texture_exist(scene->north_texture.path, "NO texture")
		|| !does_texture_exist(scene->south_texture.path, "SO texture")
		|| !does_texture_exist(scene->west_texture.path, "WE texture")
		|| !does_texture_exist(scene->east_texture.path, "EA texture"))
		ft_clean_exit(cubed, NULL, 0);
}

static void	validate_map(t_cubed *cubed)
{
	const t_map	*map = &cubed->scene.map;

	if (!map->grid)
		ft_clean_exit(cubed, ERR_MISSING_MAP, 0);
	if (!is_map_surrounded_by_walls(map))
		ft_clean_exit(cubed, ERR_MAP_NOT_SURROUNDED, 0);
	if (!has_one_start_position(map->grid))
		ft_clean_exit(cubed, ERR_START_POSITION, 0);
}

void	validate_scene(t_cubed *cubed)
{
	validate_resolution(&cubed->scene.resol);
	validate_textures(cubed);
	validate_map(cubed);
}
