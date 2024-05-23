/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:26:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/23 17:14:11 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	switch_weapon(t_cubed *cubed, int direction)
{
	t_weapon_map	*weapon_map;

	weapon_map = &cubed->weapon_map;
	weapon_map->current_weapon = (weapon_map->current_weapon + direction
			+ weapon_map->total_weapons) % weapon_map->total_weapons;
	printf("Switched to weapon %d\n", weapon_map->current_weapon);
}

int	handle_weapon_switch(int button, t_cubed *cubed)
{
	if (button == 4)
	{
		switch_weapon(cubed, 1);
	}
	else if (button == 5)
	{
		switch_weapon(cubed, -1);
	}
	return (0);
}
