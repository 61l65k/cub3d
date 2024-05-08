/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:45:21 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/08 14:45:28 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_adjacent_spaces(char **map, int i, int j)
{
	return (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
			|| map[i - 1][j + 1] == ' ' || map[i][j + 1] == ' '
			|| map[i + 1][j + 1] == ' ' || map[i + 1][j] == ' '
			|| map[i + 1][j - 1] == ' ' || map[i][j - 1] == ' ');
}

int	is_map_surrounded_by_walls(char **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
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