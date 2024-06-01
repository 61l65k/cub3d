/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:51:15 by ttakala           #+#    #+#             */
/*   Updated: 2024/06/01 16:35:14 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include <math.h>

int	t_map_add_ent(t_map *t_map, t_ent new_entity)
{
	if (t_map->entity_count >= MAX_ENTITY_COUNT)
		return (-1);
	t_map->ent[t_map->entity_count] = new_entity;
	t_map->entity_count++;
	return (0);
}

t_ent_t	t_map_get_ent_type_at(const t_map *t_map, t_coords pos, double radius)
{
	int		i;

	i = 0;
	while (i < t_map->entity_count)
	{
		if (fabs(t_map->ent[i].pos.x - pos.x) < radius
			&& fabs(t_map->ent[i].pos.y - pos.y) < radius)
			return (t_map->ent[i].type);
		i++;
	}
	return (ENT_NONE);
}

int	t_map_has_chars_at_r(const t_map *t_map, t_coords pos, double radius,
	const char *chars)
{
	int		x;
	int		y;
	char	map_char;

	x = fmax(pos.x - radius, 0);
	while (x < fmin(pos.x + radius, t_map->width))
	{
		y = fmax(pos.y - radius, 0);
		while (y < fmin(pos.y + radius, t_map->height))
		{
			map_char = t_map_get_f(t_map, x, y);
			if (ft_strchr(chars, map_char) != NULL)
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

t_coords	t_map_get_collision_checked_coords(const t_map *t_map,
	t_coords new, t_coords old)
{
	const double	collision = 0.1;

	new.x = fmin(fmax(new.x, 0.01), t_map->width - 0.01);
	new.y = fmin(fmax(new.y, 0.01), t_map->height - 0.01);
	if (!t_map_has_chars_at_r(t_map, new, collision, "1"))
		return (new);
	if (!t_map_has_chars_at_r(t_map, (t_coords){old.x, new.y}, collision, "1"))
	{
		new.x = old.x;
		return (new);
	}
	if (!t_map_has_chars_at_r(t_map, (t_coords){new.x, old.y}, collision, "1"))
	{
		new.y = old.y;
		return (new);
	}
	return (old);
}

t_coords	t_map_get_collision_checked_coords_npc(const t_map *t_map,
	t_coords new, t_coords old)
{
	const double	tile_c = 0.25;
	const double	ent_c = 0.35;

	new.x = fmin(fmax(new.x, 0.01), t_map->width - 0.01);
	new.y = fmin(fmax(new.y, 0.01), t_map->height - 0.01);
	if (!t_map_has_chars_at_r(t_map, new, tile_c, "1D")
		&& !t_map_get_ent_type_at(t_map, new, ent_c))
		return (new);
	if (!t_map_has_chars_at_r(t_map, (t_coords){old.x, new.y}, tile_c, "1D")
		&& !t_map_get_ent_type_at(t_map, (t_coords){old.x, new.y}, ent_c))
	{
		new.x = old.x;
		return (new);
	}
	if (!t_map_has_chars_at_r(t_map, (t_coords){new.x, old.y}, tile_c, "1D")
		&& !t_map_get_ent_type_at(t_map, (t_coords){new.x, old.y}, ent_c))
	{
		new.y = old.y;
		return (new);
	}
	return (old);
}
