/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:02:10 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 14:39:38 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "utils.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_X 2560
# define MAX_Y 1440

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
}				t_img;

typedef struct s_texture
{
	char		*path;
	t_img		img;
	int			width;
	int			height;
}				t_texture;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_scenedata
{
	t_texture	no_tex;
	t_texture	so_tex;
	t_texture	we_tex;
	t_texture	ea_tex;
	t_map		map;
	int			mini_map_tile_size;
}				t_scenedata;

typedef struct s_cubed
{
	t_scenedata	scene;

}				t_cubed;

void			extract_scene(t_scenedata *scene, char **av);
void			check_scene(t_cubed *cubed);
void			start_game(t_cubed *cubed);

#endif