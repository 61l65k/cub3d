/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_take_damage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:48:08 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 06:09:27 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	blend_color(int original_color, int overlay_color, float alpha)
{
	const int	original_r = (original_color >> 16) & 0xFF;
	const int	original_g = (original_color >> 8) & 0xFF;
	const int	original_b = original_color & 0xFF;
	const int	overlay_r = (overlay_color >> 16) & 0xFF;
	const int	overlay_g = (overlay_color >> 8) & 0xFF;
	const int	overlay_b = overlay_color & 0xFF;
	const int	blended_r = (int)((alpha * overlay_r) + ((1 - alpha)
					* original_r));
	const int	blended_g = (int)((alpha * overlay_g) + ((1 - alpha)
					* original_g));
	const int	blended_b = (int)((alpha * overlay_b) + ((1 - alpha)
					* original_b));

	return ((blended_r << 16) | (blended_g << 8) | blended_b);
}

static void	draw_red_frame(t_cubed *cubed, float alpha)
{
	int			i;
	int			j;
	const int	width = cubed->scene.resol.width;
	const int	height = cubed->scene.resol.height;
	int			*data;

	data = cubed->mlx.img.data;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			data[i * width + j] = blend_color(data[i * width + j], 0xFF0000,
					alpha);
		}
	}
}

void	draw_take_damage(t_cubed *cubed)
{
	float	alpha;

	alpha = 0.3;
	if (cubed->player.health <= 20)
		alpha = 0.5;
	if (cubed->player.taking_damage || cubed->player.health <= 20)
	{
		draw_red_frame(cubed, alpha);
		if (cubed->player.taking_damage)
		{
			cubed->player.damage_timer -= FIXED_FRAME_TIME;
			if (cubed->player.damage_timer <= 0)
			{
				cubed->player.taking_damage = false;
			}
		}
	}
}
