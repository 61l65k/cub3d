/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_finalize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:11:42 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/20 20:32:15 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
int	calloc_final_grid_strings(char **final_grid, size_t height, size_t width)
{
	size_t	i;

	i = 0;
	while (i < height)
	{
		final_grid[i] = ft_calloc(width + 1, sizeof(char));
		if (!final_grid[i])
		{
			while (i > 0)
				free(final_grid[--i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

static
int	strcpy_tab_to_space(const char *src, char *dst, size_t size)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while (src[i] != '\0' && j < size)
	{
		if (src[i] == '\t')
		{
			dst[j++] = ' ';
			while (j % TAB_SIZE != 0 && j < size)
				dst[j++] = ' ';
		}
		else
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
	if (src[i] != '\0')
		return (-1);
	return (0);
}

int	finalize_map(t_map *map)
{
	char			**final_grid;
	const size_t	new_size = map->height + 2;
	size_t			i;

	final_grid = ft_calloc(new_size, sizeof(char *));
	if (!final_grid)
		return (-1);
	if (calloc_final_grid_strings(final_grid, new_size - 1, map->width) == -1)
		return (free_2d_array(final_grid), -1);
	i = 0;
	while (i < map->height)
	{
		if (strcpy_tab_to_space(map->grid[i], final_grid[i], map->width) == -1)
			return (free_2d_array(final_grid), -1);
		i++;
	}
	free_2d_array(map->grid);
	map->grid = final_grid;
	map->grid_alloc_size = new_size;
	return (0);
}
