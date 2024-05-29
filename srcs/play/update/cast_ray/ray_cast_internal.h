/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:24:01 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/29 17:32:18 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_INTERNAL_H
# define RAY_CAST_INTERNAL_H

# include "vector_types.h"

typedef struct s_raycast_helper
{
	t_xy_double			a;
	double				a_x;
	double				a_y;
	t_xy_double			step;
	double				x_step;
	double				y_step;
	double				ray_section;
	int					is_south_direction;
	int					is_east_direction;
}						t_raycast_helper;

#endif