/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:05:09 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 19:24:35 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_img(t_cubed *cubed)
{
	draw_ceiling(cubed);
	draw_floor(cubed);
	// draw_walls(cubed); use rays to draw walls
}
