/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:32:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 11:42:28 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_game_x(t_cubed *cubed)
{
	ft_clean_exit(cubed, NULL);
	return (1);
}

static int	key_press(int keycode, t_cubed *cubed)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == K_ESC)
		ft_clean_exit(cubed, NULL);
	if (keycode == K_W || keycode == K_FORWARD_ARROW)
	{
		cubed->player.z_move += 1;
	}
	if (keycode == K_S || keycode == K_BACK_ARROW)
	{
		cubed->player.z_move -= 1;
	}
	if (keycode == K_D)
	{
		cubed->player.x_move += 1;
	}
	if (keycode == K_A)
	{
		cubed->player.x_move -= 1;
	}
	if (keycode == K_SPACE)
	{
		cubed->player.shooting = 1;
		cubed->scene.shooting_animation.curr_frame = 0;
		cubed->scene.shooting_animation.frame_timer = cubed->scene.shooting_animation.frame_delay;
		handle_shooting(cubed);
	}
	if (keycode == K_M)
	{
		if (cubed->game_state == GAME_STATE_RUNNING)
			cubed->game_state = GAME_STATE_MENU;
		else
			cubed->game_state = GAME_STATE_RUNNING;
	}
	if (keycode == K_LEFT_ARROW)
		cubed->player.turn_direction -= 1;
	if (keycode == K_RIGHT_ARROW)
		cubed->player.turn_direction += 1;
	return (1);
}

static int	key_released(int keycode, t_cubed *cubed)
{
	if (keycode == K_LEFT_ARROW)
		cubed->player.turn_direction += 1;
	if (keycode == K_RIGHT_ARROW)
		cubed->player.turn_direction -= 1;
	if (keycode == K_W || keycode == K_FORWARD_ARROW)
	{
		cubed->player.z_move -= 1;
	}
	if (keycode == K_S || keycode == K_BACK_ARROW)
	{
		cubed->player.z_move += 1;
	}
	else if (keycode == K_D)
	{
		cubed->player.x_move -= 1;
	}
	if (keycode == K_A)
	{
		cubed->player.x_move += 1;
	}
	return (1);
}

void	prepare_events(t_cubed *cubed)
{
	const t_mlx	*mlx = &cubed->mlx;

	mlx_do_key_autorepeatoff(cubed->mlx.mlx_ptr);
	mlx_hook(mlx->win, KEY_PRESS, M_KEY_PRESS, key_press, cubed);
	mlx_hook(mlx->win, DESTROY_NOTIFY, M_DESTROY_NOTIFY, close_game_x, cubed);
	mlx_hook(cubed->mlx.win, KEY_RELEASE, M_KEY_RELEASE, key_released, cubed);
	hook_mouse(cubed);
}
