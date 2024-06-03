/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   book_of_wisdom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:25:04 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 14:52:59 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_game(t_cubed *cubed)
{
	cubed->game_state = GAME_STATE_OVER;
}

static void	spawn_book_of_wisdom(t_cubed *cubed, double x, double y)
{
	t_item_info	*i;
	t_item		*new_item;

	i = &cubed->scene.sprite_info.item_info;
	new_item = ft_calloc(1, sizeof(t_item));
	if (!new_item)
		ft_clean_exit(cubed, ERR_ITEM_MALLOC, 0);
	new_item->type = ITEM_BOOK;
	new_item->x = x;
	new_item->y = y;
	new_item->time_since_drop = 0;
	new_item->distance = get_distance(cubed->player.x, cubed->player.y, x, y);
	new_item->next = i->items;
	update_render_info(cubed, x, y, &new_item->info);
	i->items = new_item;
	i->item_count++;
}

bool	check_and_spawn_book_of_wisdom(t_cubed *cubed, double x, double y)
{
	if (cubed->scene.sprite_info.sprites_count == 0
		&& cubed->scene.sprite_info.spawner_count == 0
		&& cubed->scene.sprite_info.boss_count == 0)
	{
		spawn_book_of_wisdom(cubed, x, y);
		return (true);
	}
	return (false);
}
