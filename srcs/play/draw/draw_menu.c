/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:41 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 14:23:50 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_menu_image(t_cubed *cubed)
{
	t_rectangle	menu;
	const int	screen_width = cubed->scene.resol.width;
	const int	screen_height = cubed->scene.resol.height;

	menu.width = screen_width / 3;
	menu.height = screen_height / 3;
	menu.x = (screen_width - menu.width) / 2;
	menu.y = (screen_height - menu.height) / 2;
	menu.border_width = 0;
	menu.fill_color = 0x555555;
	menu.border_color = 0;
	draw_rectangle(&menu, cubed->mlx.img.data, screen_width);
	mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
		cubed->mlx.img.img_ptr, 0, 0);
}

static void	draw_menu_choices(t_cubed *cubed)
{
	int	screen_width;
	int	screen_height;
	int	menu_x;
	int	menu_y;

	if (cubed->game_state == GAME_STATE_MENU)
	{
		screen_width = cubed->scene.resol.width;
		screen_height = cubed->scene.resol.height;
		menu_x = (screen_width - (screen_width / 3)) / 2;
		menu_y = (screen_height - (screen_height / 3)) / 2;
		mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y
			+ 30, 0xFFFFFF, "Resume");
		mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y
			+ 70, 0xFFFFFF, "Settings");
		mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y
			+ 110, 0xFFFFFF, "Exit");
	}
}

void	draw_menu(t_cubed *cubed)
{
	draw_menu_image(cubed);
	draw_menu_choices(cubed);
}