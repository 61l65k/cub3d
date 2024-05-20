/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_finalize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:11:42 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/20 19:08:18 by ttakala          ###   ########.fr       */
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
	const size_t	len = ft_strlen(src);
	size_t			i;
	size_t			offset;

	i = 0;
	offset = 0;
	while (i + offset < size && i < len)
	{
		if (src[i] == '\t')
		{
			dst[i + offset++] = ' ';
			while (offset % 4 != 0 && i + offset < size && i < len)
				dst[i + offset++] = ' ';
		}
		else
			dst[i + offset] = src[i];
		i++;
	}
	if (dst[size + offset] != '\0')
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
