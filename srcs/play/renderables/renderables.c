/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:43:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 10:29:16 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_wall(t_cubed *cubed, t_ray *ray, int *i)
{
	t_wall	wall;
	int		x;

	wall = (t_wall){0};
	if (!ray->orientation)
	{
		*i += 1;
		return (NO_WALL);
	}
	x = ray - cubed->rays.ray_array;
	wall.x = x;
	wall.height = get_wall_height(cubed, ray);
	wall.y = get_y_wall_position(cubed, wall.height);
	wall.texture = get_wall_texture(&cubed->scene, ray->orientation);
	render_wall_column(&wall, cubed->mlx.img.data, &cubed->scene.resol, ray);
	return (0);
}

static void	draw_renderables(t_cubed *cubed, t_renderable *renderables,
		int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (renderables[i].type == RENDERABLE_WALL)
		{
			if (render_wall(cubed, renderables[i].data.ray, &i) == NO_WALL)
				continue ;
		}
		else if (renderables[i].type == RENDERABLE_SPRITE)
			draw_any_sprite(cubed, &renderables[i].data.sprite->info,
				&renderables[i].data.sprite->texture);
		else if (renderables[i].type == RENDERABLE_SPAWNER)
			draw_any_sprite(cubed, &renderables[i].data.spawner->info,
				&renderables[i].data.spawner->spawner_texture);
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
