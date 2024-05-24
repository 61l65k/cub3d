/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:27:36 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 01:07:00 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_cubed *cubed, void *mlx, t_texture *texture)
{
	printf("Loading texture HERE %s\n", texture->path);
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
	load_weapons(cubed, &cubed->weapon_map);
}

void	prepare_rays(t_cubed *cubed)
{
	cubed->rays.ray_array = ft_calloc(cubed->scene.resol.width, sizeof(t_ray));
	if (!cubed->rays.ray_array)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC CUB_ERROR_MALLOC);
	cubed->rays.field_of_view = deg2rad(FOV);
	cubed->rays.proj_plane_dist = ((double)cubed->scene.resol.width / 2)
		/ tan(cubed->rays.field_of_view / 2);
}
