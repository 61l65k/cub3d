/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderable.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:40:16 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 18:30:32 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERABLE_H
# define RENDERABLE_H
# define NO_WALL 1
# define ERR_ALLOC_RENDERABLES "Failed to allocate memory for renderables"

typedef struct s_ray				t_ray;
typedef struct s_sprite				t_sprite;
typedef struct s_sprite_spawner		t_sprite_spawner;
typedef struct s_cubed				t_cubed;
typedef struct s_scenedata			t_scenedata;
typedef struct s_texture			t_texture;
typedef struct s_sprite_render_info	t_sprite_render_info;
typedef struct s_sprite_boss		t_sprite_boss;

typedef enum e_renderable_type
{
	RENDERABLE_WALL,
	RENDERABLE_SPRITE,
	RENDERABLE_SPAWNER,
	RENDERABLE_BOSS,
}									t_renderable_type;

typedef struct s_renderable
{
	double							distance;
	t_renderable_type				type;
	union							u_data
	{
		t_ray						*ray;
		t_sprite					*sprite;
		t_sprite_spawner			*spawner;
		t_sprite_boss				*boss;
	} data;
}									t_renderable;

void								sort_and_draw_renderables(t_cubed *cubed);
void								draw_any_sprite(t_cubed *cubed,
										t_sprite_render_info *info,
										t_texture *texture);
double								get_wall_height(t_cubed *cubed, t_ray *ray);
int									get_y_wall_position(t_cubed *cubed,
										double wall_height);
t_texture							get_wall_texture(t_scenedata *scene,
										char orientation);
t_renderable						*collect_renderables(t_cubed *cubed,
										int *count);
#endif
