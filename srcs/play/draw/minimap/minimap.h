/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:45:17 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/26 21:14:06 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

// Minimap size in map units drawn around the player
# define MMAP_SIZE 10

typedef struct t_coords
{
	double		x;
	double		y;
}				t_coords;

typedef struct s_minimap
{
	t_coords	start;
	int			dimension;
	double		scale;
}				t_minimap;

#endif