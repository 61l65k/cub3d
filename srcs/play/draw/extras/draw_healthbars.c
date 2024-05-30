/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_healthbars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:21:40 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 16:45:35 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_health_bar(t_cubed *cubed)
{
	const int			bar_width = cubed->scene.resol.width / 5;
	const int			bar_height = cubed->scene.resol.height / 20 - 5;
	const float			health_percentage = (float)cubed->player.health
		/ (float)PLAYER_MAX_HEALTH;
	const t_rectangle	background = {cubed->scene.resol.width / 50,
		cubed->scene.resol.height - bar_height - cubed->scene.resol.height / 50,
		bar_width, bar_height,
		0xFF0000, 0x000000, 0};
	const t_rectangle	foreground = {cubed->scene.resol.width / 50,
		cubed->scene.resol.height - bar_height - cubed->scene.resol.height / 50,
		(int)(bar_width * health_percentage), bar_height,
		0x00FF00, 0x000000, 0};

	draw_rectangle(&background, cubed->mlx.img.data, cubed->scene.resol.width);
	draw_rectangle(&foreground, cubed->mlx.img.data, cubed->scene.resol.width);
}
