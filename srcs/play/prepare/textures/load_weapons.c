/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:51:42 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 12:15:11 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		load_texture(t_cubed *cubed, void *mlx, t_texture *texture);

static void	load_weapon_animation(t_cubed *cubed, t_weapon *weapon,
		char **paths)
{
	int	i;

	i = -1;
	while (++i < weapon->shooting_animation.frame_count)
	{
		weapon->shooting_animation.frames[i].path = ft_strdup(paths[i]);
		if (!weapon->shooting_animation.frames[i].path)
			ft_clean_exit(cubed, ERR_LOAD_WEAPON, 0);
		load_texture(cubed, cubed->mlx.mlx_ptr,
			&weapon->shooting_animation.frames[i]);
	}
}

static void	load_weapon(t_cubed *cubed, t_weapon *weapon, char *texture_path,
		char **animation_paths)
{
	t_texture	*text;

	text = &weapon->texture;
	text->img.img_ptr = mlx_xpm_file_to_image(cubed->mlx.mlx_ptr, texture_path,
			&text->width, &text->height);
	if (!weapon->texture.img.img_ptr)
		ft_clean_exit(cubed, ERR_LOAD_WEAPON, 0);
	text->img.data = (int *)mlx_get_data_addr(text->img.img_ptr, &text->img.bpp,
			&text->img.size_l, &text->img.endian);
	if (!text->img.data)
		ft_clean_exit(cubed, ERR_LOAD_WEAPON, 0);
	weapon->shooting_animation.frames = ft_calloc(sizeof(t_texture),
			weapon->shooting_animation.frame_count);
	if (!weapon->shooting_animation.frames)
		ft_clean_exit(cubed, ERR_LOAD_WEAPON, 0);
	weapon->shooting_animation.frame_delay = 5;
	load_weapon_animation(cubed, weapon, animation_paths);
}

void	load_weapons(t_cubed *cubed, t_weapon_map *weapon_map)
{
	char	**weapon_paths;
	char	**animation_paths;
	int		animation_index;
	int		i;
	int		frame_count;

	weapon_paths = ft_split(WEAPON_PATHS, ':');
	animation_paths = ft_split(W_ANIMATION_PATHS, ':');
	if (!weapon_paths || !animation_paths)
		return (free_2d_array(weapon_paths), free_2d_array(animation_paths),
			ft_clean_exit(cubed, ERR_LOAD_WEAPON, 0));
	weapon_map->current_weapon = 0;
	animation_index = 0;
	frame_count = 3;
	i = -1;
	while (++i < WEAPON_MAX)
	{
		weapon_map->weapons[i].shooting_animation.frame_count = frame_count
			+ (i == 1);
		load_weapon(cubed, &weapon_map->weapons[i], weapon_paths[i],
			&animation_paths[animation_index]);
		get_gun_positions(&weapon_map->weapons[i], cubed, i);
		animation_index += frame_count;
	}
	return (free_2d_array(weapon_paths), free_2d_array(animation_paths));
}
