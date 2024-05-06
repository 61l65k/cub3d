/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:03:44 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/06 17:04:27 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTS_H
# define DATASTRUCTS_H
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
	int				width;
	int				height;
}					t_map;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_img			img;
}					t_mlx;

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
