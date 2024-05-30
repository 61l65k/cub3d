/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:26:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 19:09:49 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	switch_weapon(t_cubed *cubed, int direction)
{
	t_weapon_map	*weapon_map;

	weapon_map = &cubed->weapon_map;
	weapon_map->current_weapon = (weapon_map->current_weapon + direction
			+ WEAPON_MAX) % WEAPON_MAX;
	printf("Switched to weapon %d\n", weapon_map->current_weapon);
}

int	handle_weapon_switch(int button, t_cubed *cubed)
{
	if (button == SCROLL_UP)
	{
		switch_weapon(cubed, 1);
	}
	else if (button == SCROLL_DOWN)
	{
		switch_weapon(cubed, -1);
	}
	else if (button == K_Q)
	{
		switch_weapon(cubed, -1);
	}
	return (0);
}
