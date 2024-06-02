/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_taking_damage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:35:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 19:32:00 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_damage_to_player(t_cubed *cubed, int damage)
{
	t_player	*p;

	p = &cubed->player;
	p->health -= damage;
	if (p->health <= 0)
	{
		p->health = 0;
		p->taking_damage = false;
		cubed->game_state = GAME_STATE_OVER;
	}
	else
	{
		p->health_bar.health_percentage = (float)p->health
			/ (float)PLAYER_MAX_HEALTH;
		p->damage_cooldown = TAKE_DAMAGE_COOLDOWN_TIME;
	}
}

void	check_sprite_hit_player(t_cubed *cubed, t_sprite *sprite)
{
	const double	distance = sprite->distance;

	if (distance < SPRITE_ATTACK_RANGE
		&& cubed->player.damage_cooldown <= 0)
	{
		apply_damage_to_player(cubed, 3);
		cubed->player.taking_damage = true;
		cubed->player.damage_timer = TAKE_DAMAGE_DISPLAY_TIME;
	}
	else if (cubed->player.damage_cooldown > 0)
	{
		cubed->player.damage_cooldown -= FIXED_FRAME_TIME;
	}
}

void	check_boss_hit_player(t_cubed *cubed, t_sprite_boss *boss)
{
	const double	distance = boss->distance;

	if (distance < SPRITE_BOSS_ATTACK_RANGE
		&& cubed->player.damage_cooldown <= 0)
	{
		apply_damage_to_player(cubed, 20);
		cubed->player.taking_damage = true;
		cubed->player.damage_timer = TAKE_DAMAGE_DISPLAY_TIME;
	}
	else if (cubed->player.damage_cooldown > 0)
	{
		cubed->player.damage_cooldown -= FIXED_FRAME_TIME;
	}
}
