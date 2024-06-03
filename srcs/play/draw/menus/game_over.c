/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:26:13 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 13:42:01 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_screen(t_cubed *cubed)
{
	int			i;
	int			j;
	const int	width = cubed->scene.resol.width;
	const int	height = cubed->scene.resol.height;
	int			*data;

	data = cubed->mlx.img.data;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			data[i * width + j] = BLACK;
		}
	}
}

int	get_menu_option_color(t_cubed *cubed, int option_index)
{
	if (cubed->selected_option == option_index)
		return (RED);
	return (WHITE);
}

void	draw_game_over_screen(t_cubed *cubed)
{
	const int	center_x = cubed->scene.resol.width / 2;
	const int	center_y = cubed->scene.resol.height / 2;
	int			option_y_offset;
	int			option_count;

	option_count = 0;
	mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
		cubed->game_over_texture.img.img_ptr, (cubed->scene.resol.width
			- cubed->game_over_texture.width) / 2,
		(cubed->scene.resol.height \
		- cubed->game_over_texture.height) / 2 - 100);
	option_y_offset = 50;
	if (LINUX)
	{
		mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50,
			center_y + (option_y_offset += 50),
			get_menu_option_color(cubed, option_count++), "Play Again");
	}
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50, center_y
		+ option_y_offset,
		get_menu_option_color(cubed, option_count++), "Switch Map");
	option_y_offset += 50;
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50,
		center_y + option_y_offset,
		get_menu_option_color(cubed, option_count++), "Exit");
}
