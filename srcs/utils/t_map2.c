/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:51:15 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/30 22:24:15 by ttakala          ###   ########.fr       */
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

t_ent_t	t_map_get_entity_type_at(const t_map *t_map, t_coords pos)
{
	int		i;

	i = 0;
	while (i < t_map->entity_count)
	{
		if (fabs(t_map->entity[i].pos.x - pos.x) < 0.5
			&& fabs(t_map->entity[i].pos.y - pos.y) < 0.5)
			return (t_map->entity[i].type);
		i++;
	}
	return (ENT_NONE);
}
