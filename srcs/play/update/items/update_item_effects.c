/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_item_effects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:55:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 00:00:10 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_more_effects(t_player *p, t_item_effects *effects,
		int delta_time)
{
	if (effects->boots_effect_timer > 0)
	{
		effects->boots_effect_timer -= delta_time;
		if (effects->boots_effect_timer < 0)
		{
			effects->boots_effect_timer = 0;
			p->move_speed -= 0.1;
		}
	}
}

void	update_item_effects(t_player *p, double delta_time)
{
	t_item_effects	*effects;

	effects = &p->effects;
	if (effects->cloak_effect_timer > 0)
	{
		effects->cloak_effect_timer -= delta_time;
		if (effects->cloak_effect_timer < 0)
			effects->cloak_effect_timer = 0;
	}
	if (effects->slowdown_effect_timer > 0)
	{
		effects->slowdown_effect_timer -= delta_time;
		if (effects->slowdown_effect_timer < 0)
			effects->slowdown_effect_timer = 0;
	}
	check_more_effects(p, effects, delta_time);
}
