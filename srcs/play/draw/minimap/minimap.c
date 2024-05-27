/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:36:38 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/27 13:52:48 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static int	blend_colors(int c1, int c2, double alpha)
{
	const t_uint8_rgb	color1 = {
		.r = (c1 >> 16) & 0xFF,
		.g = (c1 >> 8) & 0xFF,
		.b = c1 & 0xFF
	};
	const t_uint8_rgb	color2 = {
		.r = (c2 >> 16) & 0xFF,
		.g = (c2 >> 8) & 0xFF,
		.b = c2 & 0xFF
	};
	const t_uint8_rgb	blend = {
		.r = (1 - alpha) * color1.r + alpha * color2.r,
		.g = (1 - alpha) * color1.g + alpha * color2.g,
		.b = (1 - alpha) * color1.b + alpha * color2.b
	};

	return ((blend.r << 16) | (blend.g << 8) | blend.b);
}

static int	map_color(int cur_color, t_coords cur_map,
	const t_player *player, const t_map *map)
{
	const char	c = t_map_get(map, cur_map.x, cur_map.y);
	const bool	is_player = (fabs(cur_map.x - player->x) < 0.5
			&& fabs(cur_map.y - player->y) < 0.5);

	if (is_player && c == '1')
		return (0x008000);
	if (c == '1')
		return (0x000000);
	if (is_player)
		return (0x80FF80);
	if (c == '0' || c == ' ')
		return (0xFFFFFF);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (0xFFFFFF);
	if (c == 'Z')
		return (0xFF0000);
	if (c == '\0')
		return (blend_colors(cur_color, 0x808080, 0.5));
	return (cur_color);
}

static t_minimap	get_minimap(const t_resolution *res, const t_player *player)
{
	const t_minimap	minimap = {
		.dimension = res->width / 4,
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
			img->data[i * res->width + j]
				= map_color(img->data[i * res->width + j], rotate, player, map);
		}
	}
}
