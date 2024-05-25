/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:43:15 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 09:47:37 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_renderable	*collect_renderables(t_cubed *cubed, int *count)
{
	int					total_count;
	t_sprite			*sprite;
	t_renderable		*renderables;
	int					idx;
	t_ray				*ray;
	t_sprite_spawner	*spawner;

	total_count = cubed->rays.ray_count
		+ cubed->scene.sprite_info.spawner_count;
	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		total_count++;
		sprite = sprite->next;
	}
	renderables = malloc(total_count * sizeof(t_renderable));
	if (!renderables)
		ft_clean_exit(cubed, "Failed to allocate memory for renderables");
	idx = 0;
	for (int i = 0; i < cubed->rays.ray_count; i++)
	{
		ray = &cubed->rays.ray_array[i];
		renderables[idx].distance = ray->distance;
		renderables[idx].type = RENDERABLE_WALL;
		renderables[idx].data.ray = ray;
		idx++;
	}
	for (int i = 0; i < cubed->scene.sprite_info.spawner_count; i++)
	{
		spawner = &cubed->scene.sprite_info.spawners[i];
		renderables[idx].distance = sqrt(pow(cubed->player.x - spawner->x, 2)
				+ pow(cubed->player.y - spawner->y, 2));
		renderables[idx].type = RENDERABLE_SPAWNER;
		renderables[idx].data.spawner = spawner;
		idx++;
	}
	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		renderables[idx].distance = sqrt(pow(cubed->player.x - sprite->x, 2)
				+ pow(cubed->player.y - sprite->y, 2));
		renderables[idx].type = RENDERABLE_SPRITE;
		renderables[idx].data.sprite = sprite;
		sprite = sprite->next;
		idx++;
	}
	*count = idx;
	return (renderables);
}

void	insertion_sort_renderables(t_renderable *arr, int n)
{
	t_renderable	key;
	int				j;

	for (int i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j].distance < key.distance)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

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
	int renderable_count;
	t_renderable *renderables;
	renderables = collect_renderables(cubed, &renderable_count);
	insertion_sort_renderables(renderables, renderable_count);
	draw_renderables(cubed, renderables, renderable_count);
	free(renderables);
}