/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:40:52 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 09:06:06 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_ray
{
	double	x;
	double	y;
	double	distance;
	char	obstacle;
	double	angle;
	char	orientation;
	char	side;
	double	x_step;
	double	y_step;
}			t_ray;

typedef struct s_rays
{
	t_ray	*ray_array;
	double	proj_plane_dist;
	double	field_of_view;
	int		ray_count;
}			t_rays;

typedef struct s_raycast_helper
{
	double	a_x;
	double	a_y;
	double	x_step;
	double	y_step;
	double	ray_section;
	bool	is_west_direction;
	bool	is_south_direction;
}			t_raycast_helper;

#endif
