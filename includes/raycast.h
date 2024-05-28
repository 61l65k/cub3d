/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:40:52 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 13:04:23 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdbool.h>
# include <stddef.h>

# define DOOR_FOUND 1
# define DOOR_NOT_FOUND 0

typedef struct s_door	t_door;

typedef struct s_ray
{
	double				x;
	double				y;
	double				distance;
	char				obstacle;
	double				angle;
	char				orientation;
	char				side;
	t_door				*door;
	bool				is_door;
}						t_ray;

typedef struct s_rays
{
	t_ray				*ray_array;
	double				proj_plane_dist;
	double				field_of_view;
	int					ray_count;
}						t_rays;

typedef struct s_raycast_helper
{
	double				a_x;
	double				a_y;
	double				x_step;
	double				y_step;
	double				ray_section;
	bool				is_west_direction;
	bool				is_south_direction;
}						t_raycast_helper;

#endif
