/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:45:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 00:34:17 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_adjacent_spaces(const t_map *map, size_t i, size_t j)
{
	int	has_space;

	has_space = 0;
	if (i > 0 && j > 0)
		has_space |= (map->grid[i - 1][j - 1] == ' ');
	if (i > 0)
		has_space |= (map->grid[i - 1][j] == ' ');
	if (i > 0 && j < map->width - 1)
		has_space |= (map->grid[i - 1][j + 1] == ' ');
	if (j < map->width - 1 && j < ft_strlen(map->grid[i]))
		has_space |= (map->grid[i][j + 1] == ' ');
	if (i < map->height - 1 && j < ft_strlen(map->grid[i]))
		has_space |= (map->grid[i + 1][j + 1] == ' ');
	if (i < map->height - 1)
		has_space |= (map->grid[i + 1][j] == ' ');
	if (i < map->height - 1 && j > 0)
		has_space |= (map->grid[i + 1][j - 1] == ' ');
	if (j > 0)
		has_space |= (map->grid[i][j - 1] == ' ');
	return (has_space);
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
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (j < ft_strlen(map->grid[i]) && map->grid[i][j] != '1'
				&& map->grid[i][j] != ' ')
			{
				if (i == 0 || j == 0 || i == map->height - 1 || j == map->width
					- 1)
					return (1);
				if (has_adjacent_spaces(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
