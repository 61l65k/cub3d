/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:53:29 by ttakala           #+#    #+#             */
/*   Updated: 2024/06/03 12:10:34 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_WALL_H
# define DRAW_WALL_H

typedef struct s_wall
{
	int			x;
	int			y;
	int			x_tex;
	double		height;
}				t_wall;

#endif
