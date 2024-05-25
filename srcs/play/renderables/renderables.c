/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:43:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 09:53:29 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_renderables(t_cubed *cubed, t_renderable *renderables, int count)
{
	t_wall	wall;
	t_ray	*ray;
	int		x;

	wall = (t_wall){0};
	for (int i = 0; i < count; i++)
	{
		if (renderables[i].type == RENDERABLE_WALL)
		{
			ray = renderables[i].data.ray;
			if (!ray->orientation)
			{
				continue ;
			}
			x = ray - cubed->rays.ray_array;
			wall.x = x;
			wall.height = get_wall_height(cubed, ray);
			wall.y = get_y_wall_position(cubed, wall.height);
			wall.texture = get_wall_texture(&cubed->scene, ray->orientation);
			render_wall_column(&wall, cubed->mlx.img.data, &cubed->scene.resol,
				ray);
		}
		else if (renderables[i].type == RENDERABLE_SPRITE)
		{
			draw_any_sprite(cubed, &renderables[i].data.sprite->info,
				&renderables[i].data.sprite->texture);
		}
		else if (renderables[i].type == RENDERABLE_SPAWNER)
		{
			draw_any_sprite(cubed, &renderables[i].data.spawner->info,
				&renderables[i].data.spawner->spawner_texture);
		}
	}
}

void	sort_and_draw_renderables(t_cubed *cubed)
{
	int				renderable_count;
	t_renderable	*renderables;

	renderables = collect_renderables(cubed, &renderable_count);
	insertion_sort_renderables(renderables, renderable_count);
	draw_renderables(cubed, renderables, renderable_count);
	free(renderables);
}
