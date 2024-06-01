/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:24:56 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 18:26:19 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_sprites(t_mlx *mlx, t_sprite_info *sprite_info);
void	free_animation(t_mlx *mlx, t_animation *animation);
void	free_weapons(t_mlx *mlx, t_weapon_map *weapon_map);
void	free_doors(t_mlx *mlx, t_sprite_info *sprite_info);
void	free_mlx(t_cubed *cubed);

void	free_texture(t_mlx *mlx, t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->path)
	{
		free(texture->path);
		texture->path = 0;
	}
	if (texture->img.img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, texture->img.img_ptr);
		texture->img.img_ptr = 0;
	}
}

void	free_cubed(t_cubed *cubed)
{
	free_texture(&cubed->mlx, &cubed->scene.north_texture);
	free_texture(&cubed->mlx, &cubed->scene.south_texture);
	free_texture(&cubed->mlx, &cubed->scene.east_texture);
	free_texture(&cubed->mlx, &cubed->scene.west_texture);
	free_texture(&cubed->mlx, &cubed->game_over_texture);
	free_weapons(&cubed->mlx, &cubed->weapon_map);
	free_sprites(&cubed->mlx, &cubed->scene.sprite_info);
	free_doors(&cubed->mlx, &cubed->scene.sprite_info);
	free_2d_array(cubed->scene.map.grid);
	if (cubed->mlx.mlx_ptr)
		free_mlx(cubed);
	if (cubed->rays.ray_array)
		free(cubed->rays.ray_array);
}

void	ft_clean_exit(t_cubed *cubed, char *msg, int reset)
{
	if (msg)
		perror(msg);
	if (cubed)
		free_cubed(cubed);
	if (msg)
		exit(EXIT_FAILURE);
	if (!reset)
		exit(EXIT_SUCCESS);
	if (reset == WRAPPER_EXIT)
		exit(WRAPPER_EXIT);
}
