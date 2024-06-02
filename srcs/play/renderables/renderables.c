/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:43:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 20:12:46 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "renderable.h"

static void	insertion_sort_renderables(t_renderable *arr, int n)
{
	t_renderable	key;
	int				i;
	int				j;

	i = 1;
	while (i < n)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j].distance < key.distance)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		i++;
	}
}

static void	render_wall(t_cubed *cubed, t_ray *ray)
{
	t_wall	wall;
	int		x;

	if (!ray->orientation)
		return ;
	wall = (t_wall){0};
	x = ray - cubed->rays.ray_array;
	wall.x = x;
	wall.height = get_wall_height(cubed, ray);
	wall.y = get_y_wall_position(cubed, wall.height);
	if (ray->obstacle == 'D')
	{
		if (get_distance(cubed->player.x, cubed->player.y, ray->x, ray->y) < 3)
			wall.texture = cubed->scene.sprite_info.door_open_texture;
		else
			wall.texture = cubed->scene.sprite_info.door_closed_texture;
	}
	else
		wall.texture = get_wall_texture(&cubed->scene, ray->orientation);
	render_wall_column(&wall, cubed->mlx.img.data, &cubed->scene.resol, ray);
}

static void	draw_renderables(t_cubed *cubed, t_renderable *renderables,
		int count)
{
	int		i;

	i = -1;
	while (++i < count)
	{
		if (renderables[i].type == RENDERABLE_WALL)
			render_wall(cubed, renderables[i].data.ray);
		else if (renderables[i].type == RENDERABLE_SPRITE)
			draw_any_sprite(cubed, &renderables[i].data.sprite->info,
				&cubed->scene.sprite_info.sprite_texture);
		else if (renderables[i].type == RENDERABLE_SPAWNER)
			draw_any_sprite(cubed, &renderables[i].data.spawner->info,
				&cubed->scene.sprite_info.spawner_texture);
		else if (renderables[i].type == RENDERABLE_BOSS)
			draw_any_sprite(cubed, &renderables[i].data.boss->info,
				&cubed->scene.sprite_info.sprite_boss_texture);
		else if (renderables[i].type == RENDERABLE_ITEM)
			draw_any_sprite(cubed, &renderables[i].data.item->info,
				&cubed->scene.sprite_info.item_info.\
				textures[renderables[i].data.item->type]);
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
