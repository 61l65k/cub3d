/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:27:36 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 08:54:40 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_game_over_image(t_cubed *cubed)
{
	cubed->game_over_texture.path = ft_strdup("assets/gameover.xpm");
	if (!cubed->game_over_texture.path)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE);
	cubed->game_over_texture.img.img_ptr = mlx_xpm_file_to_image(cubed->mlx.mlx_ptr,
			cubed->game_over_texture.path, &cubed->game_over_texture.width,
			&cubed->game_over_texture.height);
	if (!cubed->game_over_texture.img.img_ptr)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE);
	cubed->game_over_texture.img.data = (int *)mlx_get_data_addr(cubed->game_over_texture.img.img_ptr,
			&cubed->game_over_texture.img.bpp,
			&cubed->game_over_texture.img.size_l,
			&cubed->game_over_texture.img.endian);
	if (!cubed->game_over_texture.img.data)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE);
}

void	load_texture(t_cubed *cubed, void *mlx, t_texture *texture)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img.img_ptr)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE);
	texture->img.data = (int *)mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bpp, &texture->img.size_l, &texture->img.endian);
	if (!texture->img.data)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE);
	printf("Loaded texture %s, width: %d, height: %d\n", texture->path,
		texture->width, texture->height);
}

void	prepare_textures(t_cubed *cubed)
{
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.north_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.south_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.west_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.east_texture);
	load_game_over_image(cubed);
	load_weapons(cubed, &cubed->weapon_map);
}

void	prepare_rays(t_cubed *cubed)
{
	cubed->rays.ray_array = ft_calloc(cubed->scene.resol.width, sizeof(t_ray));
	if (!cubed->rays.ray_array)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC CUB_ERROR_MALLOC);
	cubed->rays.ray_count = cubed->scene.resol.width;
	cubed->rays.field_of_view = deg2rad(FOV);
	cubed->rays.proj_plane_dist = ((double)cubed->scene.resol.width / 2)
		/ tan(cubed->rays.field_of_view / 2);
}
