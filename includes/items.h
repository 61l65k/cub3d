/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:57:38 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 15:09:32 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include "display.h"

# define SPRITE_DROP_PROBABILITY 10
# define SPAWNER_DROP_PROBABILITY 30
# define BOSS_DROP_PROBABILITY 70

typedef struct s_texture	t_texture;

typedef enum e_item_type
{
	ITEM_HEALTH,
	ITEM_NUKE,
	ITEM_SUPER_SPEED,
	ITEM_POISON,
}							t_item_type;

typedef struct s_item
{
	t_item_type				type;
	t_texture				texture;
	int						x;
	int						y;
}							t_item;

typedef struct s_item_textures
{
	t_texture				health;
	t_texture				bread;
	t_texture				boots;
	t_texture				poison;
	t_texture				cloak;
}							t_item_textures;

typedef struct s_item_info
{
	t_item					*items;
	t_item_textures			item_textures;
	int						item_count;
}							t_item_info;

#endif
