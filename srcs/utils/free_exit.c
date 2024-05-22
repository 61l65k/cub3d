/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:24:56 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 14:35:25 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture(t_mlx *mlx, t_texture *texture)
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

static void	free_all_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	if (LINUX)
		mlx_destroy_display(mlx->mlx_ptr);
	if (mlx->mlx_ptr)
	{
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = 0;
	}
}

void	free_animation(t_mlx *mlx, t_animation *animation)
{
	int	i;

	i = 0;
	while (i < animation->frame_count)
	{
		free_texture(mlx, &animation->frames[i]);
		i++;
	}
	free(animation->frames);
}

void	free_weapons(t_mlx *mlx, t_weapon_map *weapon_map)
{
	int	i;

	i = 0;
	while (i < weapon_map->total_weapons)
	{
		free_texture(mlx, &weapon_map->weapons[i].texture);
		free_animation(mlx, &weapon_map->weapons[i].shooting_animation);
		i++;
	}
}

void	ft_clean_exit(t_cubed *cubed, char *msg)
{
	if (msg)
		perror(msg);
	if (cubed)
	{
		free_texture(&cubed->mlx, &cubed->scene.north_texture);
		free_texture(&cubed->mlx, &cubed->scene.south_texture);
		free_texture(&cubed->mlx, &cubed->scene.east_texture);
		free_texture(&cubed->mlx, &cubed->scene.west_texture);
		free_weapons(&cubed->mlx, &cubed->scene.weapon_map);
		free_2d_array(cubed->scene.map.grid);
		if (cubed->mlx.mlx_ptr)
			free_all_mlx(&cubed->mlx);
		if (cubed->rays.ray_array)
			free(cubed->rays.ray_array);
	}
	if (msg)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}