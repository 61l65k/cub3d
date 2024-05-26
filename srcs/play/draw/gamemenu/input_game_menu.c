/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_game_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 09:44:44 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 09:56:45 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	settings(t_cubed *cubed)
{
	cubed->game_state = GAME_STATE_RUNNING;
}

int	key_press_game_menu(int keycode, t_cubed *cubed)
{
	if (keycode == K_ENTER || keycode == K_SPACE)
	{
		if (cubed->selected_option == 0) // "Resume"
			cubed->game_state = GAME_STATE_RUNNING;
		else if (cubed->selected_option == 1) // "Settings"
			settings(cubed);
		else if (cubed->selected_option == 2) // "Exit"
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
