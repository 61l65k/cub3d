/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:43:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 12:53:43 by apyykone         ###   ########.fr       */
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
	if (ray->is_door)
	{
		wall.texture = ray->door->is_open ? cubed->scene.sprite_info.door_open_texture : cubed->scene.sprite_info.door_closed_texture;
	}
	else
	{
		wall.texture = get_wall_texture(&cubed->scene, ray->orientation);
	}
	render_wall_column(&wall, cubed->mlx.img.data, &cubed->scene.resol, ray);
	return (0);
}

static void	draw_renderables(t_cubed *cubed, t_renderable *renderables,
		int count)
{
	int		i;
	t_ray	*ray;

	i = -1;
	while (++i < count)
	{
		if (renderables[i].type == RENDERABLE_WALL)
		{
			ray = renderables[i].data.ray;
			if (render_wall(cubed, ray, &i) == NO_WALL)
				continue ;
		}
		else if (renderables[i].type == RENDERABLE_SPRITE)
		{
			draw_any_sprite(cubed, &renderables[i].data.sprite->info,
				&cubed->scene.sprite_info.sprite_texture);
		}
		else if (renderables[i].type == RENDERABLE_SPAWNER)
		{
			draw_any_sprite(cubed, &renderables[i].data.spawner->info,
				&cubed->scene.sprite_info.spawner_texture);
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
