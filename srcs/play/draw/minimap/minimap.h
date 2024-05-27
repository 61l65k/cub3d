/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:45:17 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/27 13:48:16 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdint.h>

// Minimap size in map units drawn around the player
# define MMAP_SIZE 32

typedef struct t_uint8_rgb
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
}				t_uint8_rgb;

typedef struct t_coords
{
	double		x;
	double		y;
}				t_coords;

typedef struct s_minimap
{
	int			dimension;
	double		scale;
	double		cos_angle;
	double		sin_angle;
}				t_minimap;

#endif