/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:03:44 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/15 21:24:48 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTS_H
# define DATASTRUCTS_H

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
	size_t			width;
	size_t			height;
}					t_map;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_img			img;
}					t_mlx;

typedef struct s_player
{
	double			x;
	double			y;
	char			walk_direction;
	double			move_speed;
	int				turn_direction;
	double			rotation_angle;
	double			rotation_speed;
}					t_player;

typedef struct s_scenedata
{
	t_resolution	resolution;
	t_color			floor_color;
	t_color			ceiling_color;
	t_texture		north_texture;
	t_texture		south_texture;
	t_texture		west_texture;
	t_texture		east_texture;
	t_map			map;
	int				mini_map_tile_size;
}					t_scenedata;

#endif
