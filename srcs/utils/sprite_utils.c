/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:58:43 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 09:19:50 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_texture(t_mlx *mlx, t_texture *texture);

t_sprite	*create_sprite_node(t_cubed *cubed, double x, double y,
		t_texture *texture)
{
	t_sprite	*new_sprite;

	new_sprite = malloc(sizeof(t_sprite));
	if (!new_sprite)
		ft_clean_exit(cubed, ERR_SPRITE_ALLOC, 0);
	new_sprite->x = x;
	new_sprite->y = y;
	if (!texture->is_loaded)
	{
		load_texture(cubed, cubed->mlx.mlx_ptr, texture);
		texture->is_loaded = true;
	}
	cubed->scene.sprite_info.sprites_count++;
	new_sprite->texture = *texture;
	new_sprite->speed = 0.01;
	new_sprite->health = 50;
	new_sprite->next = NULL;
	return (new_sprite);
}

void	free_all_sprites(t_sprite *sprites)
{
	t_sprite	*current_sprite;
	t_sprite	*next_sprite;

	current_sprite = sprites;
	while (current_sprite)
	{
		next_sprite = current_sprite->next;
		free(current_sprite);
		current_sprite = NULL;
		current_sprite = next_sprite;
	}
}

void	sort_sprites_by_distance(t_sprite **sprites)
{
	t_sprite	*head;
	t_sprite	*sorted;
	t_sprite	*current;
	t_sprite	*next;

	sorted = NULL;
	head = *sprites;
	while (head != NULL)
	{
		current = head;
		head = head->next;
		if (sorted == NULL || sorted->distance <= current->distance)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			next = sorted;
			while (next->next != NULL
				&& next->next->distance > current->distance)
				next = next->next;
			current->next = next->next;
			next->next = current;
		}
	}
	*sprites = sorted;
}
