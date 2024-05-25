/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:56:47 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 07:37:44 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "display.h"

# define SPRITE_SPEED_FACTOR 0.1
# define ERR_SPRITE_ALLOC "Error: sprite allocation failed"

typedef struct s_cubed		t_cubed;

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
}							t_sprite_render_info;

typedef struct s_sprite
{
	double					x;
	double					y;
	double					distance;
	double					angle;
	double					speed;
	t_sprite_render_info	info;
	t_texture				texture;
	struct s_sprite			*next;
}							t_sprite;

typedef struct s_sprite_spawner
{
	double					x;
	double					y;
	t_sprite_render_info	info;
	t_texture				spawner_texture;
	t_texture				sprite_texture;
	double					spawn_interval;
	double					time_since_last_spawn;
}							t_sprite_spawner;

typedef struct s_sprite_info
{
	t_sprite_spawner		*spawners;
	t_sprite				*sprites;
	int						spawner_count;
}							t_sprite_info;

void						prepare_sprites(t_cubed *cubed);
void						update_sprite_render_info(t_cubed *cubed);
void						draw_sprites(t_cubed *cubed);
int							calculate_tex_x(int stripe,
								t_sprite_render_info *info, t_texture *texture);
void						update_render_info(t_cubed *cubed, double sprite_x,
								double sprite_y,
								t_sprite_render_info *transform);
t_sprite					*create_sprite_node(t_cubed *cubed, double x,
								double y, t_texture *texture);
void						free_all_sprites(t_sprite *sprites);

#endif
