/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:51:15 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/31 16:00:26 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include <math.h>

int	t_map_add_entity(t_map *t_map, t_ent new_entity)
{
	if (t_map->entity_count >= MAX_ENTITY_COUNT)
		return (-1);
	t_map->entity[t_map->entity_count] = new_entity;
	t_map->entity_count++;
	return (0);
}

t_ent_type	t_map_get_entity_type_at(const t_map *t_map, t_coords pos)
{
	int		i;

	i = 0;
	while (i < t_map->entity_count)
	{
		if (fabs(t_map->entity[i].pos.x - pos.x) < 0.25
			&& fabs(t_map->entity[i].pos.y - pos.y) < 0.25)
			return (t_map->entity[i].type);
		i++;
	}
	return (ENT_NONE);
}

t_coords	t_map_get_collision_checked_coords(const t_map *t_map,
	t_coords new, t_coords old)
{
	char		map_char;

	new.x = fmin(fmax(new.x, 0.01), t_map->width - 0.01);
	new.y = fmin(fmax(new.y, 0.01), t_map->height - 0.01);
	map_char = t_map_get_f(t_map, new.x, new.y);
	if (map_char != '1')
		return (new);
	map_char = t_map_get_f(t_map, old.x, new.y);
	if (map_char != '1')
	{
		new.x = old.x;
		return (new);
	}
	map_char = t_map_get_f(t_map, new.x, old.y);
	if (map_char != '1')
	{
		new.y = old.y;
		return (new);
	}
	return (old);
}

t_coords	t_map_get_collision_checked_coords_npc(const t_map *t_map,
	t_coords new, t_coords old)
{
	char		map_char;

	new.x = fmin(fmax(new.x, 0.01), t_map->width - 0.01);
	new.y = fmin(fmax(new.y, 0.01), t_map->height - 0.01);
	map_char = t_map_get_f(t_map, new.x, new.y);
	if (map_char != '1' && map_char != 'D')
		return (new);
	map_char = t_map_get_f(t_map, old.x, new.y);
	if (map_char != '1' && map_char != 'D')
	{
		new.x = old.x;
		return (new);
	}
	map_char = t_map_get_f(t_map, new.x, old.y);
	if (map_char != '1' && map_char != 'D')
	{
		new.y = old.y;
		return (new);
	}
	return (old);
}
