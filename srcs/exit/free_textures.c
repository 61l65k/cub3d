/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:14:51 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 18:00:17 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_sprites(t_mlx *mlx, t_sprite_info *sprite_info)
{
	t_sprite_spawner	*curr_spawner;
	t_sprite_spawner	*next_spawner;

	if (sprite_info->spawners)
	{
		curr_spawner = sprite_info->spawners;
		while (curr_spawner)
		{
			free_texture(mlx, &curr_spawner->spawner_texture);
			free_texture(mlx, &curr_spawner->sprite_texture);
			next_spawner = curr_spawner->next;
			free(curr_spawner);
			curr_spawner = next_spawner;
		}
		sprite_info->spawners = NULL;
	}
	if (sprite_info->sprites)
	{
		free_all_sprites(sprite_info->sprites);
		sprite_info->sprites = NULL;
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
	while (i < WEAPON_MAX)
	{
		free_texture(mlx, &weapon_map->weapons[i].texture);
		free_animation(mlx, &weapon_map->weapons[i].shooting_animation);
		i++;
	}
}
