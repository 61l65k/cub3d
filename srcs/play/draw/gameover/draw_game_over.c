/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:26:13 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 09:10:37 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RED 0xFF0000
#define WHITE 0xFFFFFF

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
			data[i * width + j] = 0x000000;
		}
	}
}

static int	get_menu_option_color(t_cubed *cubed, int option_index)
{
	if (cubed->game_over_selected_option == option_index)
		return (RED);
	return (WHITE);
}

void	draw_game_over_screen(t_cubed *cubed)
{
	const int	center_x = cubed->scene.resol.width / 2;
	const int	center_y = cubed->scene.resol.height / 2;
	const int	image_x = (cubed->scene.resol.width
				- cubed->game_over_texture.width) / 2;
	const int	image_y = (cubed->scene.resol.height
				- cubed->game_over_texture.height) / 2 - 100;
	const int	play_color = get_menu_option_color(cubed, 0);
	const int	switch_map_color = get_menu_option_color(cubed, 1);
	const int	exit_color = get_menu_option_color(cubed, 2);

	mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
		cubed->game_over_texture.img.img_ptr, image_x, image_y);
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50, center_y
		+ 50, play_color, "Play Again");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50, center_y
		+ 100, switch_map_color, "Switch Map");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50, center_y
		+ 150, exit_color, "Exit");
}
