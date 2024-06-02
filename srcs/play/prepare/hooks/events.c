/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:32:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 13:46:29 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			handle_mouse_move(int x, int y, t_cubed *cubed);
int			handle_mouse_button(int button, int x, int y, t_cubed *cubed);
void		key_press_movement(int keycode, t_cubed *cubed);
void		key_release_movement(int keycode, t_cubed *cubed);
int			key_press_game_menu(int keycode, t_cubed *cubed);
int			key_press_game_over(int keycode, t_cubed *cubed);

static int	close_game_x(t_cubed *cubed)
{
	ft_clean_exit(cubed, NULL, 0);
	return (1);
}

static int	key_press_game_running(t_cubed *cubed, int keycode)
{
	if (keycode == K_ESC)
		ft_clean_exit(cubed, NULL, 0);
	key_press_movement(keycode, cubed);
	if (keycode == K_SPACE)
		cubed->player.shooting = 1;
	if (keycode == K_M)
		cubed->game_state = GAME_STATE_MENU;
	if (keycode == K_Q)
		handle_weapon_switch(K_Q, cubed);
	if (keycode == K_1)
		cubed->weapon_map.current_weapon = WEAPON_AKIMBOS;
	if (keycode == K_2)
		cubed->weapon_map.current_weapon = WEAPON_RAYGUN;
	if (keycode == K_3)
		cubed->weapon_map.current_weapon = WEAPON_MINIGUN;
	if (keycode == K_4)
		cubed->weapon_map.current_weapon = WEAPON_WRENCH;
	return (1);
}

static int	key_press(int keycode, t_cubed *cubed)
{
	if (cubed->game_state == GAME_STATE_OVER)
		return (key_press_game_over(keycode, cubed));
	if (cubed->game_state == GAME_STATE_MENU)
		return (key_press_game_menu(keycode, cubed));
	if (cubed->game_state == GAME_STATE_RUNNING)
		return (key_press_game_running(cubed, keycode));
	return (1);
}

static int	key_released(int keycode, t_cubed *cubed)
{
	key_release_movement(keycode, cubed);
	if (keycode == K_SPACE)
		cubed->player.shooting = 0;
	return (1);
}

void	prepare_events(t_cubed *cubed)
{
	const t_mlx	*mlx = &cubed->mlx;
	t_mouse		*mouse;

	mouse = &cubed->mouse;
	mouse->last_x = -1;
	mlx_do_key_autorepeatoff(cubed->mlx.mlx_ptr);
	mlx_hook(mlx->win, KEY_PRESS, M_KEY_PRESS, key_press, cubed);
	mlx_hook(mlx->win, DESTROY_NOTIFY, M_DESTROY_NOTIFY, close_game_x, cubed);
	mlx_hook(cubed->mlx.win, KEY_RELEASE, M_KEY_RELEASE, key_released, cubed);
	mlx_hook(mlx->win, 4, 1L << 2, handle_mouse_button, cubed);
	mlx_hook(mlx->win, 6, 1L << 6, handle_mouse_move, cubed);
}
