/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:03:55 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/27 14:44:59 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H

# include <stddef.h>

typedef struct s_map
{
	char	**grid;
	size_t	grid_alloc_size;
	size_t	width;
	size_t	height;
}			t_map;

char		t_map_get(const t_map *t_map, int x, int y);
char		t_map_get_f(const t_map *t_map, double x, double y);
void		t_map_print(const t_map *t_map);
int			t_map_insert(t_map *t_map, int x, int y, char new_value);

#endif
