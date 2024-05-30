/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_healthbars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:21:40 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 17:45:48 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_health_bar(t_player *p, int screen_width, int screen_height)
{
	p->health_bar.bar_width = screen_width / 5;
	p->health_bar.bar_height = screen_height / 20 - 5;
	p->health_bar.bar_x = screen_width / 50;
	p->health_bar.bar_y = screen_height - p->health_bar.bar_height
		- screen_height / 50;
	p->health_bar.health_percentage = (float)p->health
		/ (float)PLAYER_MAX_HEALTH;
	p->health_bar.initialized = true;
}

static void	draw_player_health_bar(t_cubed *cubed)
{
	const t_health_bar	*hb = &cubed->player.health_bar;
	const t_rectangle	background = {hb->bar_x, hb->bar_y, hb->bar_width,
		hb->bar_height, RED, BLACK, 0};
	const t_rectangle	foreground = {hb->bar_x, hb->bar_y,
		(int)(hb->bar_width * hb->health_percentage),
		hb->bar_height, HBAR_GREEN, BLACK, 0};

	draw_rectangle(&background, cubed->mlx.img.data, cubed->scene.resol.width);
	draw_rectangle(&foreground, cubed->mlx.img.data, cubed->scene.resol.width);
}

void	draw_healthbars(t_cubed *cubed)
{
	if (cubed->player.health_bar.initialized == false)
	{
		init_health_bar(&cubed->player, cubed->scene.resol.width,
			cubed->scene.resol.height);
	}
	draw_player_health_bar(cubed);
}
