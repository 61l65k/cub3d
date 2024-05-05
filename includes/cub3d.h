/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:02:10 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/05 20:19:55 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "utils.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_X_RES 2560
# define MAX_Y_RES 1440

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

typedef struct s_cubed
{
	t_scenedata		scene;
	t_mlx			mlx;

}					t_cubed;

void				extract_scene(t_cubed *cubed, char **av);
void				extract_map(t_cubed *cubed, int fd, char *line);
void				validate_scene(t_cubed *cubed);
void				start_game(t_cubed *cubed);

#endif