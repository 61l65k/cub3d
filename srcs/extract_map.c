/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:21:38 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/04 16:48:44 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map(int fd, char *line, t_map *map)
{
	int		i;
	int		alloc_size;
	char	**tmp_map;

	i = 0;
	alloc_size = 2;
	tmp_map = malloc(alloc_size * sizeof(char *));
	if (!tmp_map)
		return (perror(CUB_ERROR_MALLOC "get_map()\n"), -1);
	while (1)
	{
		if (i >= alloc_size - 1)
		{
			alloc_size *= 2;
			tmp_map = ft_realloc(tmp_map, (i + 1) * sizeof(char *), alloc_size
					* sizeof(char *));
			if (!tmp_map)
				return (perror(CUB_ERROR_MALLOC "get_map()\n"), -1);
		}
		tmp_map[i++] = ft_strdup(line);
		if (!tmp_map[i - 1])
			return (perror(CUB_ERROR_MALLOC "get_map()\n"), -1);
		free(line);
		if (!gnl(fd, &line) && *line == 0)
			break ;
	}
	free(line);
	tmp_map[i] = 0;
	map->grid = tmp_map;
	map->height = i;
	return (0);
}

void	extract_map(t_cubed *cubed, int fd, char *line)
{
	if (get_map(fd, line, &cubed->scene.map) < 0)
		ft_clean_exit(cubed, "Error\nFailed to extract map");
	for (int i = 0; i < cubed->scene.map.height; i++)
		printf("%s\n", cubed->scene.map.grid[i]);
}
