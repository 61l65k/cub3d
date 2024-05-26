/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_taking_damage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:35:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 06:21:28 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DAMAGE_THRESHOLD 0.5
#define DAMAGE_DISPLAY_TIME 10.0
#define DAMAGE_COOLDOWN_TIME 7.0

static void	apply_damage_to_player(t_cubed *cubed, int damage)
{
	cubed->player.health -= damage;
	if (cubed->player.health <= 0)
	{
		cubed->player.health = 0;
		cubed->player.taking_damage = false;
		// kill_player(cubed);
	}
	else
	{
		cubed->player.damage_cooldown = DAMAGE_COOLDOWN_TIME;
	}
}

void	check_sprite_hit_player(t_cubed *cubed, t_sprite *sprite)
{
	const double	distance = sqrt(pow(cubed->player.x - sprite->x, 2)
				+ pow(cubed->player.y - sprite->y, 2));

	if (distance < DAMAGE_THRESHOLD && cubed->player.damage_cooldown <= 0)
	{
		apply_damage_to_player(cubed, 3);
		cubed->player.taking_damage = true;
		cubed->player.damage_timer = DAMAGE_DISPLAY_TIME;
	}
	else if (cubed->player.damage_cooldown > 0)
	{
		cubed->player.damage_cooldown -= FIXED_FRAME_TIME;
	}
}
