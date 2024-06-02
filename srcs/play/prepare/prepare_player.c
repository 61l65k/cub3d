/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:14 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 13:35:32 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				player->x = j + 0.5;
				player->y = i + 0.5;
				player->rotation_angle = get_orientation(grid[i][j]);
				grid[i][j] = '0';
				return ;
			}
		}
	}
}

void	prepare_player(t_cubed *cubed)
{
	t_player	*player;

	player = &cubed->player;
	ft_memset(player, 0, sizeof(t_player));
	get_starting_position(&cubed->player, cubed->scene.map.grid);
	player->dir_x = cos(player->rotation_angle);
	player->dir_y = sin(player->rotation_angle);
	player->fov_rad = deg2rad(FOV);
	player->fov_scaling_factor = tan(player->fov_rad / 2);
	player->health = PLAYER_MAX_HEALTH;
	player->damage_cooldown = TAKE_DAMAGE_COOLDOWN_TIME;
	player->move_speed = 0.03;
	player->rotation_speed = deg2rad(0.6);
	if (!LINUX)
	{
		player->move_speed *= 2.5;
		player->rotation_speed *= 2.5;
	}
}
