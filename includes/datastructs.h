/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:03:44 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 11:19:37 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTS_H
# define DATASTRUCTS_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_resolution
{
	int				width;
	int				height;
}					t_resolution;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				argb;
}					t_color;

typedef struct s_img
{
	void			*img_ptr;
	int				*data;
	int				bpp;
	int				size_l;
	int				endian;
}					t_img;

typedef struct s_texture
{
	char			*path;
	t_img			img;
	int				width;
	int				height;
}					t_texture;

typedef struct s_map
{
	char			**grid;
	size_t			grid_alloc_size;
	size_t			width;
	size_t			height;
}					t_map;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_img			img;
}					t_mlx;

typedef struct s_drawable_rect
{
	int				x;
	int				y;
	double			width;
	double			height;
	int				fill_color;
	int				border_color;
	int				border_width;
	t_texture		tex;
}					t_drawable_rect;

typedef struct s_player
{
	double			x;
	double			y;
	int				x_move;
	int				z_move;
	double			move_speed;
	int				turn_direction;
	double			rotation_angle;
	double			rotation_speed;
	bool			shooting;
}					t_player;

typedef struct s_ray
{
	double			x;
	double			y;
	double			size;
	char			obstacle;
	double			angle;
	char			orientation;
	char			side;
	double			x_step;
	double			y_step;
}					t_ray;

typedef struct s_rays
{
	t_ray			*ray_array;
	double			proj_plane_dist;
	double			view_angle;
}					t_rays;

typedef struct s_rectangle
{
	int				x;
	int				y;
	double			width;
	double			height;
	int				fill_color;
	int				border_color;
	int				border_width;
}					t_rectangle;

typedef struct s_wall
{
	int				x;
	int				y;
	double			width;
	double			height;
	t_texture		texture;
}					t_wall;

typedef struct s_raycast_helper
{
	double			a_x;
	double			a_y;
	double			x_step;
	double			y_step;
	double			ray_section;
	bool			is_west_direction;
	bool			is_south_direction;
}					t_raycast_helper;

typedef struct s_animation
{
	t_texture		*frames;
	int				frame_count;
	int				curr_frame;
	int				frame_delay;
	int				frame_timer;
}					t_animation;

typedef struct s_scenedata
{
	t_resolution	resolution;
	t_color			floor_color;
	t_color			ceiling_color;
	t_texture		north_texture;
	t_texture		south_texture;
	t_texture		west_texture;
	t_texture		east_texture;
	t_texture		gun_texture;
	t_animation		shooting_animation;
	t_map			map;
	int				mini_map_tile_size;
}					t_scenedata;

typedef struct s_mouse
{
	bool			active;
	int				last_x;
	bool			mouse_was_reset;
	bool			mouse_skip_update;
}					t_mouse;

#endif
