/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:58:18 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/29 12:54:15 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_resolution(t_resolution *resolution)
{
	if (resolution->width < 1 || resolution->height < 1)
	{
		printf(DEFAULT_RESOL_MSG);
		resolution->width = 1920;
		resolution->height = 1080;
	}
	if (resolution->width > MAX_X_RES)
		resolution->width = MAX_X_RES;
	if (resolution->height > MAX_Y_RES)
		resolution->height = MAX_Y_RES;
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
