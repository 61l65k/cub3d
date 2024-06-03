/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:41 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 15:09:51 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			get_menu_option_color(t_cubed *cubed, int option_index);

int	key_press_game_menu(int keycode, t_cubed *cubed)
{
	if (keycode == K_ENTER)
	{
		if (cubed->selected_option == 0)
			cubed->game_state = GAME_STATE_RUNNING;
		else if (cubed->selected_option == 1)
			ft_clean_exit(cubed, NULL, WRAPPER_EXIT);
		else if (cubed->selected_option == 2)
			ft_clean_exit(cubed, NULL, 0);
	}
	else if (keycode == K_FORWARD_ARROW || keycode == K_W)
		cubed->selected_option = (cubed->selected_option - 1 + 3) % 3;
	else if (keycode == K_BACK_ARROW || keycode == K_S)
		cubed->selected_option = (cubed->selected_option + 1) % 3;
	else if (keycode == K_ESC)
		ft_clean_exit(cubed, NULL, 0);
	return (1);
}

static void	draw_menu_image(t_cubed *cubed)
{
	t_rectangle	menu;
	const int	screen_width = cubed->scene.resol.width;
	const int	screen_height = cubed->scene.resol.height;

	menu.width = (int)(screen_width / 3);
	menu.height = (int)(screen_height / 3);
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

	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y + 30,
		get_menu_option_color(cubed, 0), "Resume");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y + 70,
		get_menu_option_color(cubed, 1), "Switch Map");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, menu_x + 20, menu_y
		+ 110, get_menu_option_color(cubed, 2), "Exit");
}

void	draw_menu(t_cubed *cubed)
{
	draw_menu_image(cubed);
	draw_menu_choices(cubed);
}
