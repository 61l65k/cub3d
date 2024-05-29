/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:41 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/29 12:53:01 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define GREY 0x555555

int			get_menu_option_color(t_cubed *cubed, int option_index);

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
	menu.fill_color = GREY;
	menu.border_color = 0;
	draw_rectangle(&menu, cubed->mlx.img.data, screen_width);
	mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
		cubed->mlx.img.img_ptr, 0, 0);
}

static void	draw_menu_choices(t_cubed *cubed)
{
	const int	screen_width = cubed->scene.resol.width;
	const int	screen_height = cubed->scene.resol.height;
	const int	menu_x = (screen_width - (screen_width / 3)) / 2;
	const int	menu_y = (screen_height - (screen_height / 3)) / 2;
	const int	resume_color = get_menu_option_color(cubed, 0);
	const int	settings_color = get_menu_option_color(cubed, 1);
	const int	exit_color = get_menu_option_color(cubed, 2);

	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y + 30,
		resume_color, "Resume");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y + 70,
		settings_color, "Settings");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y
		+ 110, exit_color, "Exit");
}

void	draw_menu(t_cubed *cubed)
{
	draw_menu_image(cubed);
	draw_menu_choices(cubed);
}
