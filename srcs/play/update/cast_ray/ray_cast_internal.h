/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:24:01 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/31 23:01:41 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_INTERNAL_H
# define RAY_CAST_INTERNAL_H

# define DOOR_OPENING_DISTANCE 1.0

typedef enum e_ray_orientation
{
	X_AXIS_INTERSECTION,
	Y_AXIS_INTERSECTION
}						t_ray_orientation;

typedef struct s_raycast_helper
{
	double				x_step;
	double				y_step;
	double				ray_section;
}						t_raycast_helper;

#endif