/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_take_damage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:48:08 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 17:26:57 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			data[i * width + j] = blend_colors(data[i * width + j], 0xFF0000,
					alpha);
		}
	}
}

void	draw_take_damage(t_cubed *cubed)
{
	float		alpha;
	const int	critical_health = 35;

	alpha = 0.3;
	if (cubed->player.health <= critical_health)
		alpha = 0.5;
	if (cubed->player.taking_damage || cubed->player.health <= critical_health)
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
