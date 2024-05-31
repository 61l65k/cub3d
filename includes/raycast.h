/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:40:52 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 13:45:46 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_ray
{
	double				x;
	double				y;
	double				distance;
	double				angle;
	char				obstacle;
	char				orientation;
}						t_ray;

typedef struct s_rays
{
	t_ray				*ray_array;
	double				proj_plane_dist;
	double				field_of_view;
	int					ray_count;
}						t_rays;

#endif