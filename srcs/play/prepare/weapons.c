/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:51:42 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 13:44:26 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		load_texture(t_cubed *cubed, void *mlx, t_texture *texture);

#define MAX_WEAPONS 10

static void	switch_weapon(t_cubed *cubed, int direction)
{
	t_weapon_map	*weapon_map;

	weapon_map = &cubed->scene.weapon_map;
	weapon_map->current_weapon = (weapon_map->current_weapon + direction
			+ weapon_map->total_weapons) % weapon_map->total_weapons;
	printf("Switched to weapon %d\n", weapon_map->current_weapon);
}

int	handle_weapon_switch(int button, t_cubed *cubed)
{
	if (button == 4)
	{
		switch_weapon(cubed, 1);
	}
	else if (button == 5)
	{
		switch_weapon(cubed, -1);
	}
	return (0);
}

static void	load_weapon(t_cubed *cubed, void *mlx, t_weapon *weapon,
		const char *texture_path, const char **animation_paths, int frame_count)
{
	weapon->texture.img.img_ptr = mlx_xpm_file_to_image(mlx,
			(char *)texture_path, &weapon->texture.width,
			&weapon->texture.height);
	if (!weapon->texture.img.img_ptr)
		ft_clean_exit(cubed,
			"mlx_xpm_file_to_image() failed for weapon texture\n");
	weapon->texture.img.data = (int *)mlx_get_data_addr(weapon->texture.img.img_ptr,
			&weapon->texture.img.bpp, &weapon->texture.img.size_l,
			&weapon->texture.img.endian);
	if (!weapon->texture.img.data)
		ft_clean_exit(cubed, "mlx_get_data_addr() failed for weapon texture\n");
	printf("Loaded weapon texture %s, width: %d, height: %d\n", texture_path,
		weapon->texture.width, weapon->texture.height);
	weapon->shooting_animation.frames = (t_texture *)malloc(sizeof(t_texture)
			* frame_count);
	if (!weapon->shooting_animation.frames)
		ft_clean_exit(cubed,
			"Failed to allocate memory for animation frames\n");
	weapon->shooting_animation.frame_count = frame_count;
	weapon->shooting_animation.curr_frame = 0;
	weapon->shooting_animation.frame_delay = 5;
	weapon->shooting_animation.frame_timer = 0;
	for (int i = 0; i < frame_count; i++)
	{
		weapon->shooting_animation.frames[i].path = ft_strdup(animation_paths[i]);
		if (!weapon->shooting_animation.frames[i].path)
			ft_clean_exit(cubed,
				"Failed to allocate memory for animation frame path\n");
		load_texture(cubed, mlx, &weapon->shooting_animation.frames[i]);
	}
}

void	load_weapons(t_cubed *cubed, void *mlx, t_weapon_map *weapon_map)
{
	const char	**animation_paths;
	int			frame_count;

	const char *weapon_textures[] = {
		"./assets/weapons/akimbos/akimbos.xpm",
		"./assets/weapons/hammer/hammer.xpm",
		"./assets/weapons/raygun/raygun.xpm",
	};
	const char *weapon1_animation_paths[] = {
		"./assets/weapons/akimbos/cloud_fire0.xpm",
		"./assets/weapons/akimbos/cloud_fire1.xpm",
		"./assets/weapons/akimbos/cloud_fire2.xpm",
	};
	const char *weapon2_animation_paths[] = {
		"./assets/weapons/hammer/cloud_magic_trail0.xpm",
		"./assets/weapons/hammer/cloud_magic_trail1.xpm",
		"./assets/weapons/hammer/cloud_magic_trail2.xpm",
		"./assets/weapons/hammer/cloud_magic_trail3.xpm",
	};
	const char *weapon3_animation_paths[] = {
		"./assets/weapons/raygun/cloud_poison0.xpm",
		"./assets/weapons/raygun/cloud_poison1.xpm",
		"./assets/weapons/raygun/cloud_poison2.xpm",
	};
	weapon_map->total_weapons = 3;
	weapon_map->current_weapon = 0;
	for (int i = 0; i < weapon_map->total_weapons; i++)
	{
		frame_count = 3;
		if (i == 0)
			animation_paths = weapon1_animation_paths;
		if (i == 1)
		{
			animation_paths = weapon2_animation_paths;
			frame_count = 4;
		}
		if (i == 2)
			animation_paths = weapon3_animation_paths;
		load_weapon(cubed, mlx, &weapon_map->weapons[i], weapon_textures[i],
			animation_paths, frame_count);
	}
}
