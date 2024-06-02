/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:02:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 20:23:37 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	remove_expired_items(t_cubed *cubed, t_item **current,
		t_item **prev)
{
	if (*prev)
		(*prev)->next = (*current)->next;
	else
		cubed->scene.sprite_info.item_info.items = (*current)->next;
	free(*current);
	if (*prev)
		*current = (*prev)->next;
	else
		*current = cubed->scene.sprite_info.item_info.items;
	cubed->scene.sprite_info.item_info.item_count--;
}

void	update_active_item(t_cubed *cubed, t_item *item)
{
	const t_player	*p = &cubed->player;

	item->distance = get_distance(p->x, p->y, item->x, item->y);
	update_render_info(cubed, item->x, item->y, &item->info);
	item->time_since_drop += ITEM_TIME_INCREMENT;
	item->info.health_bar.health_percentage = (item->time_since_drop
			/ ITEM_DROP_LIFETIME) * 100.0;
}

void	update_all_items(t_cubed *cubed)
{
	t_item	*i;
	t_item	*prev_i;

	i = cubed->scene.sprite_info.item_info.items;
	prev_i = NULL;
	while (i)
	{
		if (i->time_since_drop >= ITEM_DROP_LIFETIME)
		{
			remove_expired_items(cubed, &i, &prev_i);
		}
		else
		{
			update_active_item(cubed, i);
			prev_i = i;
			i = i->next;
		}
	}
}
