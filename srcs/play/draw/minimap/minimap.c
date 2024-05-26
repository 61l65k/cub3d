/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:36:38 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/26 21:54:47 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static int	map_color(double x, double y, const t_map *map)
{
	const char	c = t_map_get(map, x, y);

	if (c == '1')
		return (0x000000);
	else if (c == '0' || c == ' ')
		return (0xFFFFFF);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (0xFFFFFF);
	else if (c == 'Z')
		return (0xFF0000);
	else if (c == '\0')
		return (0x808080);
	return (0x00FF00);
}

void	draw_minimap(t_img *img,
	const t_resolution *res,
	const t_map *map,
	const t_player *player)
{
	const t_minimap	m = {
		.start = {player->x - MMAP_SIZE / 2.0, player->y - MMAP_SIZE / 2.0},
		.dimension = res->width / 8,
		.scale = (double)MMAP_SIZE / m.dimension
	};
	int				i;
	int				j;

	i = -1;
	while (++i < m.dimension)
	{
		j = -1;
		while (++j < m.dimension)
		{
			img->data[j * res->width + i]
				= map_color(m.start.x + i * m.scale,
					m.start.y + j * m.scale,
					map);
		}
	}
}
