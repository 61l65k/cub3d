/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:30:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 03:32:08 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_tex_x(int stripe, t_sprite_render_info *info, t_texture *texture)
{
	return ((int)(256 * (stripe - (-info->sprite_width / 2
					+ info->sprite_screen_x)) * texture->width
			/ info->sprite_width) / 256);
}
