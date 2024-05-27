/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:36:38 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/27 12:50:05 by ttakala          ###   ########.fr       */
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

static t_minimap	get_minimap(const t_resolution *res, const t_player *player)
{
	const t_minimap	minimap = {
		.dimension = res->width / 8,
		.scale = (double)MMAP_SIZE / minimap.dimension,
		.cos_angle = cos(player->rotation_angle),
		.sin_angle = sin(player->rotation_angle)
	};

	return (minimap);
}

void	draw_minimap(t_img *img,
	const t_resolution *res,
	const t_map *map,
	const t_player *player)
{
	const t_minimap	m = get_minimap(res, player);
	int				i;
	int				j;
	t_coords		rel;
	t_coords		rotate;

	i = -1;
	while (++i < m.dimension)
	{
		j = -1;
		while (++j < m.dimension)
		{
			rel.x = -((i - m.dimension / 2.0) * m.scale);
			rel.y = (j - m.dimension / 2.0) * m.scale;
			rotate.x = rel.x * m.cos_angle - rel.y * m.sin_angle + player->x;
			rotate.y = rel.x * m.sin_angle + rel.y * m.cos_angle + player->y;
			img->data[i * res->width + j] = map_color(rotate.x, rotate.y, map);
		}
	}
}
