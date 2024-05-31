/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_healthbars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:21:40 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 12:34:29 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_health_bar(t_player *p, int screen_width, int screen_height)
{
	p->health_bar.width = screen_width / 5;
	p->health_bar.height = screen_height / 20 - 5;
	p->health_bar.x = screen_width / 50;
	p->health_bar.y = screen_height - p->health_bar.height
		- screen_height / 50;
	p->health_bar.health_percentage = (float)p->health
		/ (float)PLAYER_MAX_HEALTH;
	p->health_bar.initialized = true;
}

static void	draw_player_health_bar(t_cubed *cubed)
{
	const t_health_bar	*hb = &cubed->player.health_bar;
	const t_rectangle	background = {hb->x, hb->y, hb->width,
		hb->height, RED, BLACK, 0};
	const t_rectangle	foreground = {hb->x, hb->y,
		(int)(hb->width * hb->health_percentage),
		hb->height, HBAR_GREEN, BLACK, 0};

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
