/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:14 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 06:37:11 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	center_of_tile(int pos)
{
	return (pos + 0.5);
}

static double	get_orientation(char orientation)
{
	double	radian;

	radian = 0;
	if (orientation == 'N')
		radian = deg2rad(270);
	else if (orientation == 'S')
		radian = deg2rad(90);
	else if (orientation == 'E')
		radian = deg2rad(360);
	else if (orientation == 'W')
		radian = deg2rad(180);
	return (radian);
}

static void	get_starting_position(t_player *player, char **grid)
{
	int	i;
	int	j;

	i = -1;
	while (grid[++i])
	{
		j = -1;
		while (grid[i][++j])
		{
			if (ft_strchr("NSEW", grid[i][j]))
			{
				player->x = center_of_tile(j);
				player->y = center_of_tile(i);
				player->rotation_angle = get_orientation(grid[i][j]);
				grid[i][j] = '0';
			}
		}
	}
}

void	prepare_player(t_cubed *cubed)
{
	t_player	*player;

	player = &cubed->player;
	player->x_move = 0;
	player->z_move = 0;
	player->move_speed = 0.02;
	player->turn_direction = 0;
	player->rotation_speed = deg2rad(0.5);
	player->dir_x = cos(player->rotation_angle);
	player->dir_y = sin(player->rotation_angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	get_starting_position(&cubed->player, cubed->scene.map.grid);
}
