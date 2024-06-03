/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:57:38 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 14:19:28 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include "display.h"

# define ERR_ITEM_MALLOC "Error: Item malloc failed\n"
# define ITEM_DROP_LIFETIME 7.0
# define ITEM_TIME_INCREMENT 0.010
# define ITEM_PICKUP_THRESHOLD 1.0

typedef struct s_texture	t_texture;
typedef struct s_item_info	t_item_info;

typedef enum e_effect_timers
{
	CLOAK_EFFECT_TIME = 5,
	BOOTS_EFFECT_TIME = 5,
	POISON_EFFECT_TIME = 5,
}							t_effect_timers;

typedef enum e_item_type
{
	ITEM_NONE = -1,
	ITEM_HEALTH,
	ITEM_BREAD,
	ITEM_BOOTS,
	ITEM_POISON,
	ITEM_CLOAK,
	ITEM_BOOK,
	ITEM_MAX
}							t_item_type;

typedef struct s_item_probability
{
	t_item_type				type;
	int						cumulative_probability;
}							t_item_probability;

typedef struct s_sprite_render_info
{
	double					transform_x;
	double					transform_y;
	int						sprite_screen_x;
	int						sprite_height;
	int						sprite_width;
	int						draw_start_x;
	int						draw_end_x;
	int						draw_start_y;
	int						draw_end_y;
	t_health_bar			health_bar;
}							t_sprite_render_info;

typedef struct s_item
{
	t_item_type				type;
	t_sprite_render_info	info;
	int						x;
	int						y;
	double					distance;
	double					time_since_drop;
	struct s_item			*next;
}							t_item;

typedef struct s_item_info
{
	t_item					*items;
	t_texture				textures[ITEM_MAX];
	int						item_count;
	int						spawn_attempt_counter;
}							t_item_info;

typedef struct s_item_effects
{
	double					boots_effect_timer;
	double					cloak_effect_timer;
	double					slowdown_effect_timer;
	double					slowdown_factor;
}							t_item_effects;

#endif
