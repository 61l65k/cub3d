/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:27:36 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 15:14:12 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_game_over_image(t_cubed *cubed)
{
	t_texture	*gme;
	const char	*gme_path = "./assets/default/gameover.xpm";

	gme = &cubed->game_over_texture;
	gme->path = ft_strdup(gme_path);
	if (!gme->path)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
	gme->img.img_ptr = mlx_xpm_file_to_image(cubed->mlx.mlx_ptr, gme->path,
			&gme->width, &gme->height);
	if (!gme->img.img_ptr)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
	gme->img.data = (int *)mlx_get_data_addr(gme->img.img_ptr, &gme->img.bpp,
			&gme->img.size_l, &gme->img.endian);
	if (!gme->img.data)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
}

void	load_texture(t_cubed *cubed, void *mlx, t_texture *texture)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img.img_ptr)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
	texture->img.data = (int *)mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bpp, &texture->img.size_l, &texture->img.endian);
	if (!texture->img.data)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
}

static void	load_sprite_textures(t_cubed *cubed)
{
	t_sprite_info	*i;
	const char		*sprite = "./assets/default/boggart.xpm";
	const char		*spawner = "./assets/default/spawner.xpm";

	i = &cubed->scene.sprite_info;
	if (!i->sprite_texture.path)
	{
		i->sprite_texture.path = ft_strdup(sprite);
		if (!i->sprite_texture.path)
			ft_clean_exit(cubed, CUB_ERROR_MALLOC CUB_ERROR_MALLOC, 0);
	}
	if (!i->spawner_texture.path)
	{
		i->spawner_texture.path = ft_strdup(spawner);
		if (!i->spawner_texture.path)
			ft_clean_exit(cubed, CUB_ERROR_MALLOC CUB_ERROR_MALLOC, 0);
	}
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->sprite_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->spawner_texture);
}

void	prepare_textures(t_cubed *cubed)
{
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.north_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.south_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.west_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.east_texture);
	load_sprite_textures(cubed);
	load_game_over_image(cubed);
	load_weapons(cubed, &cubed->weapon_map);
}

void	prepare_rays(t_cubed *cubed)
{
	cubed->rays.ray_array = ft_calloc(cubed->scene.resol.width, sizeof(t_ray));
	if (!cubed->rays.ray_array)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC CUB_ERROR_MALLOC, 0);
	cubed->rays.ray_count = cubed->scene.resol.width;
	cubed->rays.field_of_view = deg2rad(FOV);
	cubed->rays.proj_plane_dist = ((double)cubed->scene.resol.width / 2)
		/ tan(cubed->rays.field_of_view / 2);
}
