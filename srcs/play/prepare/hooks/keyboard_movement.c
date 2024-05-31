/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:32:55 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/31 21:37:32 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_press_movement(int keycode, t_cubed *cubed)
{
	if (keycode == K_W || keycode == K_FORWARD_ARROW)
		cubed->player.z_move += 1;
	if (keycode == K_S || keycode == K_BACK_ARROW)
		cubed->player.z_move -= 1;
	if (keycode == K_D)
		cubed->player.x_move += 1;
	if (keycode == K_A)
		cubed->player.x_move -= 1;
	if (keycode == K_LEFT_ARROW)
		cubed->player.turn_direction -= 1;
	if (keycode == K_RIGHT_ARROW)
		cubed->player.turn_direction += 1;
	if (keycode == K_LEFT_SHIFT)
		cubed->player.move_speed *= 2;
}

void	key_release_movement(int keycode, t_cubed *cubed)
{
	if (keycode == K_LEFT_ARROW)
		cubed->player.turn_direction += 1;
	if (keycode == K_RIGHT_ARROW)
		cubed->player.turn_direction -= 1;
	if (keycode == K_W || keycode == K_FORWARD_ARROW)
		cubed->player.z_move -= 1;
	if (keycode == K_S || keycode == K_BACK_ARROW)
		cubed->player.z_move += 1;
	else if (keycode == K_D)
		cubed->player.x_move -= 1;
	if (keycode == K_A)
		cubed->player.x_move += 1;
	if (keycode == K_LEFT_SHIFT)
		cubed->player.move_speed /= 2;
}
