/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:27:36 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 21:55:01 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_cubed *cubed, void *mlx, t_texture *texture)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img.img_ptr)
		ft_clean_exit(cubed, "mlx_xpm_file_to_image() failed\n");
	texture->img.data = (int *)mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bpp, &texture->img.size_l, &texture->img.endian);
	if (!texture->img.data)
		ft_clean_exit(cubed, "mlx_get_data_addr() failed\n");
	printf("Loaded texture %s, width: %d, height: %d\n", texture->path,
		texture->width, texture->height);
}

static void	load_gun_texture(t_cubed *cubed, void *mlx, t_texture *texture,
		const char *path)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx, (char *)path,
			&texture->width, &texture->height);
	if (!texture->img.img_ptr)
		ft_clean_exit(cubed, "mlx_xpm_file_to_image() failed for gun image\n");
	texture->img.data = (int *)mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bpp, &texture->img.size_l, &texture->img.endian);
	if (!texture->img.data)
		ft_clean_exit(cubed, "mlx_get_data_addr() failed for gun image\n");
	printf("Loaded gun image %s, width: %d, height: %d\n", path, texture->width,
		texture->height);
}

void	load_animation(t_cubed *cubed, t_animation *animation,
		const char **frame_paths, int frame_count)
{
	animation->frames = (t_texture *)malloc(sizeof(t_texture) * frame_count);
	if (!animation->frames)
		ft_clean_exit(cubed,
			"Failed to allocate memory for animation frames\n");
	animation->frame_count = frame_count;
	animation->curr_frame = 0;
	animation->frame_delay = 5;
	animation->frame_timer = 0;
	for (int i = 0; i < frame_count; i++)
	{
		animation->frames[i].path = ft_strdup(frame_paths[i]);
		if (!animation->frames[i].path)
			ft_clean_exit(cubed,
				"Failed to allocate memory for animation frame path\n");
		load_texture(cubed, cubed->mlx.mlx_ptr, &animation->frames[i]);
	}
}

void	prepare_textures(t_cubed *cubed)
{
	const char *shooting_frame_paths[] = {
		"./assets/gun/cloud_fire0.xpm",
		"./assets/gun/cloud_fire1.xpm",
		"./assets/gun/cloud_fire2.xpm",
	};
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.north_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.south_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.west_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.east_texture);
	load_gun_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.gun_texture,
		GUN_TEXTURE_PATH);
	load_animation(cubed, &cubed->scene.shooting_animation,
		shooting_frame_paths, 3);
}

void	prepare_rays(t_cubed *cubed)
{
	cubed->rays.ray_array = ft_calloc(cubed->scene.resolution.width,
			sizeof(t_ray));
	if (!cubed->rays.ray_array)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC "set_rays()\n");
	cubed->rays.view_angle = deg2rad(VIEW_ANGLE);
	cubed->rays.proj_plane_dist = ((double)cubed->scene.resolution.width / 2)
		/ tan(cubed->rays.view_angle / 2);
}
