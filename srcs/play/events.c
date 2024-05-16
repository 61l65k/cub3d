/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:32:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 16:33:45 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_game_x(t_cubed *cubed)
{
	ft_clean_exit(cubed, NULL);
	return (1);
}

static int	key_press(int keycode, t_cubed *cubed)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == K_ESC)
		ft_clean_exit(cubed, NULL);
	return (1);
}

void	prepare_events(t_cubed *cubed)
{
	const t_mlx	*mlx = &cubed->mlx;

	mlx_hook(mlx->win, KEY_PRESS, M_KEY_PRESS, key_press, cubed);
	mlx_hook(mlx->win, DESTROY_NOTIFY, M_DESTROY_NOTIFY, close_game_x, cubed);
	// mlx_hook(mlx->win, 3, 1L << 1, key_release, cubed);
	// mlx_hook(mlx->win, 17, 1L << 17, close_game, cubed);
}
