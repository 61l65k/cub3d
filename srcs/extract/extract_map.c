/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:21:38 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 19:04:54 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	realloc_map(t_map *map)
{
	size_t	new_alloc_size;

	new_alloc_size = map->grid_alloc_size * 2;
	map->grid = ft_realloc(map->grid,
			map->grid_alloc_size * sizeof(char *),
			new_alloc_size * sizeof(char *));
	if (!map->grid)
	{
		map->grid_alloc_size = 0;
		return (perror(CUB_ERROR_MALLOC "realloc_map()"), -1);
	}
	map->grid_alloc_size = new_alloc_size;
	return (0);
}

static int	get_map(int fd, char **line, t_map *map)
{
	size_t	i;
	int		gnl_ret;

	i = 0;
	while (1)
	{
		if (i + 1 >= map->grid_alloc_size)
		{
			if (realloc_map(map))
				return (free_null(line), -1);
		}
		map->grid[i++] = ft_strdup(*line);
		free_null(line);
		if (!map->grid[i - 1])
			return (perror(CUB_ERROR_MALLOC "get_map()"), -1);
		gnl_ret = gnl(fd, line);
		if (gnl_ret < 0)
			return (perror("get_map(): gnl() fail"), -1);
		if (gnl_ret == 0)
			break ;
	}
	free_null(line);
	map->grid[i] = NULL;
	map->height = i;
	return (0);
}

static int	get_map_width(char **strs)
{
	size_t	max_length;
	size_t	length;
	int		i;
	int		j;

	max_length = 0;
	i = 0;
	while (strs[i])
	{
		length = 0;
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '\t')
				length += 4;
			else
				length++;
			j++;
		}
		if (length > max_length)
			max_length = length;
		i++;
	}
	return (max_length);
}

int	extract_map(t_cubed *cubed, int fd, char **line)
{
	int	status;

	status = 0;
	cubed->scene.map.grid_alloc_size = 80;
	cubed->scene.map.grid
		= ft_calloc(cubed->scene.map.grid_alloc_size, sizeof(char *));
	if (!cubed->scene.map.grid)
		return (perror(CUB_ERROR_MALLOC "extract_map(1) malloc fail"), -1);
	status = get_map(fd, line, &cubed->scene.map);
	if (status)
	{
		ft_fprintf(STDERR_FILENO, "extract_map(2): get_map() failed\n");
		return (status);
	}
	cubed->scene.map.width = get_map_width(cubed->scene.map.grid);
	return (status);
}
