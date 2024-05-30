/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:03:55 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/30 18:30:50 by ttakala          ###   ########.fr       */
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

typedef struct s_map
{
	char	**grid;
	size_t	grid_alloc_size;
	size_t	width;
	size_t	height;
}			t_map;

char		t_map_get(const t_map *t_map, int x, int y);
char		t_map_get_f(const t_map *t_map, double x, double y);
int			t_map_insert(t_map *t_map, int x, int y, char new_value);
int			t_map_insert_f(t_map *t_map, double x, double y, char new_value);
t_coords	t_map_get_collision_checked_coords(const t_map *t_map,
				t_coords new, t_coords old);

#endif
