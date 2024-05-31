/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:03:55 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/31 16:00:42 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H

# include <stddef.h>

typedef struct s_coords
{
	double		x;
	double		y;
}				t_coords;

typedef enum e_ent_type
{
	ENT_NONE,
	ENT_GENERIC,
	ENT_MAX
}				t_ent_type;

typedef struct s_ent
{
	t_coords	pos;
	t_ent_type	type;
}				t_ent;

# define MAX_ENTITY_COUNT 100

typedef struct s_map
{
	char		**grid;
	size_t		grid_alloc_size;
	size_t		width;
	size_t		height;
	t_ent		entity[MAX_ENTITY_COUNT];
	int			entity_count;
}			t_map;

char		t_map_get(const t_map *t_map, int x, int y);
char		t_map_get_f(const t_map *t_map, double x, double y);
int			t_map_insert(t_map *t_map, int x, int y, char new_value);
int			t_map_insert_f(t_map *t_map, double x, double y, char new_value);
t_coords	t_map_get_collision_checked_coords(const t_map *t_map,
				t_coords new, t_coords old);
t_coords	t_map_get_collision_checked_coords_npc(const t_map *t_map,
				t_coords new, t_coords old);
int			t_map_add_entity(t_map *t_map, t_ent new_entity);
t_ent_type	t_map_get_entity_type_at(const t_map *t_map, t_coords pos);

#endif
