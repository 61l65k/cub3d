/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:45:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 19:11:01 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_adjacent_spaces(const t_map *map, int y, int x)
{
	char	map_char;
	int		y_cur;
	int		x_cur;

	y_cur = y - 1;
	while (y_cur <= y + 1)
	{
		x_cur = x - 1;
		while (x_cur <= x + 1)
		{
			if (y_cur == y && x_cur == x)
			{
				x_cur++;
				continue ;
			}
			map_char = t_map_get(map, x_cur, y_cur);
			if (map_char == ' ' || map_char == '\0')
				return (1);
			x_cur++;
		}
		y_cur++;
	}
	return (0);
}

int	has_one_start_position(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				count++;
		}
	}
	return (count == 1);
}

int	is_map_surrounded_by_walls(const t_map *map)
{
	int		y;
	int		x;
	char	map_char;

	y = 0;
	while (y < (int)map->height)
	{
		x = 0;
		while (x < (int)map->width)
		{
			map_char = t_map_get(map, x, y);
			if (map_char != '1' && map_char != ' ' && map_char != '\0')
			{
				if (has_adjacent_spaces(map, y, x))
					return (ft_fprintf(STDERR_FILENO, MAP_ERR_LOC, y, x), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
