/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:20:55 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 18:32:56 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_probabilities(t_item_probability *sprite_probs,
		t_item_probability *spawner_probs, t_item_probability *boss_probs)
{
	sprite_probs[0] = (t_item_probability){ITEM_NONE, 50};
	sprite_probs[1] = (t_item_probability){ITEM_HEALTH, 60};
	sprite_probs[2] = (t_item_probability){ITEM_POISON, 70};
	sprite_probs[3] = (t_item_probability){ITEM_BOOTS, 80};
	sprite_probs[4] = (t_item_probability){ITEM_CLOAK, 90};
	sprite_probs[5] = (t_item_probability){ITEM_BREAD, 100};
	spawner_probs[0] = (t_item_probability){ITEM_NONE, 50};
	spawner_probs[1] = (t_item_probability){ITEM_HEALTH, 60};
	spawner_probs[2] = (t_item_probability){ITEM_POISON, 70};
	spawner_probs[3] = (t_item_probability){ITEM_BOOTS, 80};
	spawner_probs[4] = (t_item_probability){ITEM_CLOAK, 90};
	spawner_probs[5] = (t_item_probability){ITEM_BREAD, 100};
	boss_probs[0] = (t_item_probability){ITEM_NONE, 50};
	boss_probs[1] = (t_item_probability){ITEM_HEALTH, 60};
	boss_probs[2] = (t_item_probability){ITEM_POISON, 70};
	boss_probs[3] = (t_item_probability){ITEM_BOOTS, 80};
	boss_probs[4] = (t_item_probability){ITEM_CLOAK, 90};
	boss_probs[5] = (t_item_probability){ITEM_BREAD, 100};
}

t_item_type	get_item_type(int *counter, t_sprite_type entity_type)
{
	const int			count = ITEM_MAX + 1;
	const int			threshold = (*counter * 100 / (count)) % 100;
	int					i;
	t_item_probability	probabilities[ITEM_MAX + 1];
	t_item_probability	sprite_probs[ITEM_MAX + 1];
	t_item_probability	spawner_probs[ITEM_MAX + 1];
	t_item_probability	boss_probs[ITEM_MAX + 1];

	get_probabilities(sprite_probs, spawner_probs, boss_probs);
	if (entity_type == SPRITE)
		ft_memcpy(probabilities, sprite_probs, sizeof(sprite_probs));
	else if (entity_type == SPAWNER)
		ft_memcpy(probabilities, spawner_probs, sizeof(spawner_probs));
	else if (entity_type == BOSS)
		ft_memcpy(probabilities, boss_probs, sizeof(boss_probs));
	i = -1;
	(*counter)++;
	while (++i < ITEM_MAX + 1)
	{
		if (threshold < probabilities[i].cumulative_probability)
			return (probabilities[i].type);
	}
	return (probabilities[count - 1].type);
}

void	spawn_item(t_cubed *cubed, double x, double y,
		t_sprite_type entity_type)
{
	const t_item_type	type = get_item_type(&cubed->scene.sprite_info.item_info.spawn_attempt_counter,
				entity_type);
	t_item_info			*i;
	t_item				*new_item;

	if (type == ITEM_NONE)
		return ;
	i = &cubed->scene.sprite_info.item_info;
	new_item = ft_calloc(1, sizeof(t_item));
	if (!new_item)
		ft_clean_exit(cubed, ERR_ITEM_MALLOC, 0);
	new_item->type = type;
	new_item->texture = i->textures[type];
	new_item->x = x;
	new_item->y = y;
	new_item->time_since_drop = 0;
	new_item->distance = get_distance(cubed->player.x, cubed->player.y, x, y);
	new_item->next = i->items;
	update_render_info(cubed, x, y, &new_item->info);
	i->items = new_item;
	i->item_count++;
	printf("Item spawned at x: %f, y: %f\n", x, y);
}

void	update_all_items(t_cubed *cubed)
{
	const t_player	*p = &cubed->player;
	t_item			*i;
	t_item			*prev_i;

	i = cubed->scene.sprite_info.item_info.items;
	prev_i = 0;
	while (i)
	{
		if (i->time_since_drop >= ITEM_DROP_LIFETIME)
		{
			if (prev_i)
				prev_i->next = i->next;
			else
				cubed->scene.sprite_info.item_info.items = i->next;
			free(i);
			if (prev_i)
				i = prev_i->next;
			else
				i = cubed->scene.sprite_info.item_info.items;
			cubed->scene.sprite_info.item_info.item_count--;
		}
		else
		{
			i->distance = get_distance(p->x, p->y, i->x, i->y);
			update_render_info(cubed, i->x, i->y, &i->info);
			i->time_since_drop += ITEM_TIME_INCREMENT;
			prev_i = i;
			i = i->next;
		}
	}
}
