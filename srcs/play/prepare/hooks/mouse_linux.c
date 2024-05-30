/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:03:11 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 12:55:55 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOUSE_SENSITIVITY 0.001
#define MOUSE_ESCAPE_THRESHOLD 20

static void	reset_mouse_position(t_cubed *cubed, int width, int height,
		t_mouse *mouse)
{
	mlx_mouse_move(cubed->mlx.mlx_ptr, cubed->mlx.win, width / 2, height / 2);
	mouse->last_x = width / 2;
	mouse->mouse_was_reset = 1;
	mouse->mouse_skip_update = 1;
}

static void	update_rotation_angle(t_player *player, int delta_x)
{
	player->rotation_angle += delta_x * MOUSE_SENSITIVITY;
	if (player->rotation_angle < 0)
		player->rotation_angle += 2 * M_PI;
	else if (player->rotation_angle > 2 * M_PI)
		player->rotation_angle -= 2 * M_PI;
}

static int	update_x_orientation(t_mouse *mouse, int x)
{
	if (!mouse->active || mouse->last_x == -1)
	{
		mouse->last_x = x;
		return (1);
	}
	if (mouse->mouse_was_reset)
	{
		mouse->mouse_was_reset = 0;
		mouse->last_x = x;
		return (1);
	}
	if (mouse->mouse_skip_update)
	{
		mouse->mouse_skip_update = 0;
		mouse->last_x = x;
		return (1);
	}
	return (0);
}

int	handle_mouse_move(int x, int y, t_cubed *cubed)
{
	t_mouse				*mouse;
	const t_resolution	*resol = &cubed->scene.resol;
	int					delta_x;

	mouse = &cubed->mouse;
	if (update_x_orientation(mouse, x))
		return (0);
	delta_x = x - mouse->last_x;
	update_rotation_angle(&cubed->player, delta_x);
	mouse->last_x = x;
	if (x < MOUSE_ESCAPE_THRESHOLD || x > resol->width - MOUSE_ESCAPE_THRESHOLD
		|| y < MOUSE_ESCAPE_THRESHOLD || y > resol->height
		- MOUSE_ESCAPE_THRESHOLD)
	{
		reset_mouse_position(cubed, resol->width, resol->height, mouse);
	}
	return (0);
}

int	handle_mouse_button(int button, int x, int y, t_cubed *cubed)
{
	const int	x_half = cubed->scene.resol.width / 2;
	const int	y_half = cubed->scene.resol.height / 2;

	(void)x;
	(void)y;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		handle_weapon_switch(button, cubed);
	if (button == LEFT_CLICK)
		cubed->player.shooting = 1;
	if (button == RIGHT_CLICK)
	{
		if (!cubed->mouse.active)
		{
			cubed->mouse.active = 1;
			mlx_mouse_hide(cubed->mlx.mlx_ptr, cubed->mlx.win);
		}
		else
		{
			cubed->mouse.active = 0;
			mlx_mouse_show(cubed->mlx.mlx_ptr, cubed->mlx.win);
		}
		mlx_mouse_move(cubed->mlx.mlx_ptr, cubed->mlx.win, x_half, y_half);
	}
	return (0);
}
