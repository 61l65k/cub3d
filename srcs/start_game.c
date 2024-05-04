/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:39:27 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/04 20:48:11 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(t_cubed *cubed)
{
	t_mlx	*mlx_data;

	mlx_data = &cubed->mlx;
	mlx_data->mlx_ptr = mlx_init();
	if (!cubed->mlx.mlx_ptr)
		ft_clean_exit(cubed, "mlx_init() failed\n");
	// mlx_get_screen_size(mlx->mlx_ptr, &mlx->max_x,
	//&mlx->max_y); maybe in mid game user can change resolution to full ?
	mlx_data->win = mlx_new_window(mlx_data->mlx_ptr,
			cubed->scene.resolution.width, cubed->scene.resolution.height,
			"cub3D");
	if (!mlx_data->win)
		ft_clean_exit(cubed, "mlx_new_window() failed\n");
	// prepare_game(cubed);
	// mlx_loop_hook(mlx->mlx_ptr, load_frames, cubed);
	// mlx_loop(mlx_data->mlx_ptr);
}
