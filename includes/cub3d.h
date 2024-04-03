/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:02:10 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/04 02:43:34 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
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

# define ARG_ERROR_MSG "Remember to give the cub file name ./cub3d <example.cub>\n"
# define NOT_CUB_ERROR_MSG "The file is not a .cub file\n"

typedef struct s_img
{
	void	*ptr;
	int		*addr;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_line
{
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;
	int		color;
	double	deltax;
	double	deltay;
	double	pixels;
}			t_line;

typedef struct s_text
{
	char	*text_name;
	t_img	imgt;
}			t_text;

typedef struct s_ray
{
	double	fov;
	double	fovref_min;
	double	fovref_max;
	double	wall_strip_w;
	int		num_rays;
	double	distprojplane;
	double	ray_angle;
	int		facing_down;
	int		facing_left;
	double	horxstep;
	double	horystep;
	double	verxstep;
	double	verystep;
	double	wall_hit_horx;
	double	wall_hit_hory;
	double	wall_hit_verx;
	double	wall_hit_very;
	double	wall_hit_x;
	double	wall_hit_y;
	int		found_hor_wall;
	int		found_ver_wall;
	double	distance;
	int		hit_vertical;
	t_text	text_wallhit;
	t_line	line;
}			t_ray;

typedef struct s_cubed
{
	t_img	img_m;
	t_img	img_3d;
	t_line	line_3d;
	t_line	line;
	t_ray	ray;
	t_text	notext;
	t_text	sotext;
	t_text	eatext;
	t_text	wetext;
	t_line	line_sp;
	t_img	imgflr;
}			t_cubed;

#endif