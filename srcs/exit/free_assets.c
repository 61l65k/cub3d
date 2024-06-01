/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:14:51 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 18:26:16 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all_sprites(t_sprite *sprites)
{
	t_sprite	*current_sprite;
	t_sprite	*next_sprite;

	current_sprite = sprites;
	while (current_sprite)
	{
		next_sprite = current_sprite->next;
		free(current_sprite);
		current_sprite = NULL;
		current_sprite = next_sprite;
	}
	sprites = NULL;
}

void	free_sprites(t_mlx *mlx, t_sprite_info *sprite_info)
{
	t_sprite_spawner	*curr_spawner;
	t_sprite_spawner	*next_spawner;

	free_texture(mlx, &sprite_info->spawner_texture);
	free_texture(mlx, &sprite_info->sprite_texture);
	free_texture(mlx, &sprite_info->sprite_boss_texture);
	if (sprite_info->spawners)
	{
		curr_spawner = sprite_info->spawners;
		while (curr_spawner)
		{
			next_spawner = curr_spawner->next;
			free(curr_spawner);
			curr_spawner = next_spawner;
		}
		sprite_info->spawners = NULL;
	}
	if (sprite_info->sprites)
		free_all_sprites(sprite_info->sprites);
	if (sprite_info->sprite_bosses)
		free_all_sprites((t_sprite *)sprite_info->sprite_bosses);
}

void	free_doors(t_mlx *mlx, t_sprite_info *sprite_info)
{
	t_door	*current_door;
	t_door	*next_door;

	free_texture(mlx, &sprite_info->door_closed_texture);
	free_texture(mlx, &sprite_info->door_open_texture);
	current_door = sprite_info->doors;
	while (current_door)
	{
		next_door = current_door->next;
		free(current_door);
		current_door = next_door;
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
