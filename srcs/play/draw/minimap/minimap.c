/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:36:38 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/26 21:13:22 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

void	draw_minimap(t_img *img,
	const t_resolution *res,
	const t_map *map,
	const t_player *player)
{
	const t_minimap	m = {
		.start = {player->x - MMAP_SIZE / 2.0, player->y - MMAP_SIZE / 2.0},
		.dimension = res->width / 4,
		.scale = (double)MMAP_SIZE / m.dimension
	};
	char			c;
	int				i;
	int				j;

	i = -1;
	while (++i < m.dimension)
	{
		j = -1;
		while (++j < m.dimension)
		{
			c = t_map_get(map, m.start.x + i * m.scale,
					m.start.y + j * m.scale);
			if (c == '1')
				img->data[j * res->width + i] = 0x000000;
			else
				img->data[j * res->width + i] = 0xFFFFFF;
		}
	}
}
