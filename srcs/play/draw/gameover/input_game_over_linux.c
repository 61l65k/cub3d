/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_game_over.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:57:03 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 13:51:15 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	restart_game(t_cubed *cubed)
{
	cubed->reset = true;
	if (LINUX)
		mlx_loop_end(cubed->mlx.mlx_ptr);
}

static void	switch_map(t_cubed *cubed)
{
	cubed->game_state = GAME_STATE_RUNNING;
}

int	key_press_game_over(int keycode, t_cubed *cubed)
{
	if (keycode == K_ENTER || keycode == K_SPACE)
	{
		if (cubed->selected_option == 0)
			restart_game(cubed);
		else if (cubed->selected_option == 1)
			switch_map(cubed);
		else if (cubed->selected_option == 2)
			ft_clean_exit(cubed, NULL, 0);
	}
	else if (keycode == K_FORWARD_ARROW || keycode == K_W)
	{
		cubed->selected_option = (cubed->selected_option - 1 + 3) % 3;
	}
	else if (keycode == K_BACK_ARROW || keycode == K_S)
	{
		cubed->selected_option = (cubed->selected_option + 1) % 3;
	}
	else if (keycode == K_ESC)
	{
		ft_clean_exit(cubed, NULL, 0);
	}
	return (1);
}
