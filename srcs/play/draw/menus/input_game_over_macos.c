/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_game_over_macos.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:57:03 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 13:52:17 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_game_over(int keycode, t_cubed *cubed)
{
	if (keycode == K_ENTER)
	{
		if (cubed->selected_option == 0)
			ft_clean_exit(cubed, NULL, WRAPPER_EXIT);
		else if (cubed->selected_option == 1)
			ft_clean_exit(cubed, NULL, 0);
	}
	else if (keycode == K_FORWARD_ARROW || keycode == K_W)
	{
		cubed->selected_option = (cubed->selected_option - 1 + 2) % 2;
	}
	else if (keycode == K_BACK_ARROW || keycode == K_S)
	{
		cubed->selected_option = (cubed->selected_option + 1) % 2;
	}
	else if (keycode == K_ESC)
	{
		ft_clean_exit(cubed, NULL, 0);
	}
	return (1);
}
