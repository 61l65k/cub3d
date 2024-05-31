/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:36:17 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 16:47:44 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <stdbool.h>

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_rectangle
{
	int			x;
	int			y;
	double		width;
	double		height;
	int			fill_color;
	int			border_color;
	int			border_width;
}				t_rectangle;

typedef struct s_resolution
{
	int			width;
	int			height;
}				t_resolution;

typedef struct s_mouse
{
	bool		active;
	int			last_x;
	bool		mouse_was_reset;
	bool		mouse_skip_update;
}				t_mouse;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
}				t_mlx;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
	int			argb;
	bool 		initialized;
}				t_color;

typedef struct s_texture
{
	char		*path;
	t_img		img;
	int			width;
	int			height;
}				t_texture;

typedef struct s_wall
{
	int			x;
	int			y;
	double		width;
	double		height;
	t_texture	texture;
}				t_wall;

typedef struct s_health_bar
{
	int			x;
	int			y;
	int			width;
	int			height;
	float		health_percentage;
	bool		initialized;
}				t_health_bar;

typedef struct s_animation
{
	t_texture	*frames;
	int			frame_count;
	int			curr_frame;
	int			frame_delay;
	int			frame_timer;
}				t_animation;

#endif
