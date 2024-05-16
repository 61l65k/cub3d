/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:14 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 15:12:27 by apyykone         ###   ########.fr       */
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
		radian = degree_to_radian(270);
	else if (orientation == 'S')
		radian = degree_to_radian(90);
	else if (orientation == 'E')
		radian = degree_to_radian(360);
	else if (orientation == 'W')
		radian = degree_to_radian(180);
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
	cubed->player.walk_direction = 0;
	cubed->player.move_speed = 0.15;
	cubed->player.turn_direction = 0;
	cubed->player.rotation_speed = degree_to_radian(4);
	get_starting_position(&cubed->player, cubed->scene.map.grid);
}
