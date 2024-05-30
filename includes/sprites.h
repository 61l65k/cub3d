/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:56:47 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 16:15:17 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "display.h"

# define SPRITE_SPEED_FACTOR 0.1
# define ERR_SPRITE_ALLOC "Error: sprite allocation failed"
# define SPRITE_MAX_HEALTH 50

typedef struct s_cubed		t_cubed;
typedef struct s_ray		t_ray;

typedef struct s_apply_damage_helper
{
	double					delta_dist_x;
	double					delta_dist_y;
	double					current_distance;
	int						map_x;
	int						map_y;
	double					side_dist_x;
	double					side_dist_y;
	int						step_x;
	int						step_y;
}							t_apply_damage_helper;

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
	float					health;
	t_sprite_render_info	info;
	t_texture				texture;
	struct s_sprite			*next;
}							t_sprite;

typedef struct s_sprite_spawner
{
	double					x;
	double					y;
	float					health;
	t_sprite_render_info	info;
	double					spawn_interval;
	double					time_since_last_spawn;
	t_texture				texture;
	double					distance;
	struct s_sprite_spawner	*next;
}							t_sprite_spawner;

typedef struct s_door
{
	double					x;
	double					y;
	t_texture				closed_texture;
	t_texture				open_texture;
	bool					is_open;
	double					distance;
	struct s_door			*next;
}							t_door;

typedef struct s_sprite_info
{
	t_sprite_spawner		*spawners;
	t_sprite				*sprites;
	t_door					*doors;
	t_texture				door_closed_texture;
	t_texture				door_open_texture;
	t_texture				spawner_texture;
	t_texture				sprite_texture;
	int						sprites_count;
	int						spawner_count;
}							t_sprite_info;

void						prepare_map_specials(t_cubed *cubed);
void						update_sprite_render_info(t_cubed *cubed);
void						draw_sprites(t_cubed *cubed);
void						update_render_info(t_cubed *cubed, double sprite_x,
								double sprite_y,
								t_sprite_render_info *transform);
t_sprite					*create_sprite_node(t_cubed *cubed, double x,
								double y, t_texture *texture);
void						free_all_sprites(t_sprite *sprites);
void						sort_sprites_by_distance(t_sprite **sprites);
bool						traverse_and_apply_damage(t_cubed *cubed,
								const t_ray *ray, double max_distance,
								float damage);
#endif
