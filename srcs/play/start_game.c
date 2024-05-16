/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:39:27 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 15:58:19 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare_game(t_cubed *cubed)
{
	prepare_player(cubed);
	prepare_events(cubed);
	prepare_textures(cubed);
	prepare_rays(cubed);
}

void	start_game(t_cubed *cubed)
{
	t_mlx	*mlx_data;

	mlx_data = &cubed->mlx;
	mlx_data->mlx_ptr = mlx_init();
	if (!cubed->mlx.mlx_ptr)
		ft_clean_exit(cubed, "mlx_init() failed\n");
	mlx_data->win = mlx_new_window(mlx_data->mlx_ptr,
			cubed->scene.resolution.width, cubed->scene.resolution.height,
			"cub3D");
	if (!mlx_data->win)
		ft_clean_exit(cubed, "mlx_new_window() failed\n");
	prepare_game(cubed);
	// mlx_loop_hook(mlx_data->mlx_ptr, render_frames, cubed);
	mlx_loop(mlx_data->mlx_ptr);
}
