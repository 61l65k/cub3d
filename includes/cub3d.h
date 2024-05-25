/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:02:10 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 10:52:13 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "definitions.h"
# include "libft.h"
# include "raycast.h"
# include "renderable.h"
# include "sprites.h"
# include "t_map.h"
# include "utils.h"
# include "weapon.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_game_state
{
	GAME_STATE_RUNNING,
	GAME_STATE_MENU
}					t_game_state;

typedef struct s_player
{
	double			x;
	double			y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	int				x_move;
	int				z_move;
	int				health;
	double			move_speed;
	int				turn_direction;
	double			rotation_angle;
	double			rotation_speed;
	bool			shooting;
}					t_player;

typedef struct s_scenedata
{
	t_resolution	resol;
	t_color			floor_color;
	t_color			ceiling_color;
	t_texture		north_texture;
	t_texture		south_texture;
	t_texture		west_texture;
	t_texture		east_texture;
	t_map			map;
	t_sprite_info	sprite_info;
	int				mini_map_tile_size;
}					t_scenedata;

typedef struct s_cubed
{
	t_game_state	game_state;
	t_scenedata		scene;
	t_mlx			mlx;
	t_rays			rays;
	t_player		player;
	t_mouse			mouse;
	t_weapon_map	weapon_map;
}					t_cubed;

void				validate_scene(t_cubed *cubed);
void				start_game(t_cubed *cubed);
void				prepare_textures(t_cubed *cubed);
void				prepare_rays(t_cubed *cubed);
void				prepare_player(t_cubed *cubed);
void				prepare_rays(t_cubed *cubed);
void				draw_floor(t_cubed *cubed);
void				draw_ceiling(t_cubed *cubed);
void				draw_walls(t_cubed *game);
void				cast_ray(t_ray *ray, t_map *map, t_player *player);
void				update_rays(t_cubed *game);
void				draw_gun_shooting(t_cubed *cubed);
void				draw_menu(t_cubed *cubed);
void				handle_shooting(t_cubed *cubed);
void				hook_mouse(t_cubed *cubed);
int					handle_weapon_switch(int button, t_cubed *cubed);

#endif
