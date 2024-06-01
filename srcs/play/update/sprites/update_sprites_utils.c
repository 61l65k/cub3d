/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:01:48 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 18:02:03 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*create_sprite_node(t_cubed *cubed, double x, double y,
		t_texture *texture)
{
	t_sprite	*new_sprite;

	new_sprite = ft_calloc(1, sizeof(t_sprite));
	if (!new_sprite)
		ft_clean_exit(cubed, ERR_SPRITE_ALLOC, 0);
	new_sprite->x = x;
	new_sprite->y = y;
	cubed->scene.sprite_info.sprites_count++;
	new_sprite->texture = *texture;
	new_sprite->speed = 0.2;
	if (!LINUX)
		new_sprite->speed = 0.4;
	new_sprite->health = SPRITE_MAX_HEALTH;
	return (new_sprite);
}
