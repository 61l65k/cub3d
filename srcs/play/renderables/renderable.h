/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderable.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:40:16 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 13:04:56 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERABLE_H
# define RENDERABLE_H
# define NO_WALL 1

typedef struct s_ray				t_ray;
typedef struct s_sprite				t_sprite;
typedef struct s_sprite_spawner		t_sprite_spawner;
typedef struct s_cubed				t_cubed;
typedef struct s_scenedata			t_scenedata;
typedef struct s_texture			t_texture;
typedef struct s_sprite_render_info	t_sprite_render_info;

typedef enum e_renderable_type
{
	RENDERABLE_WALL,
	RENDERABLE_SPRITE,
	RENDERABLE_SPAWNER,
}									t_renderable_type;

typedef struct s_renderable
{
	double							distance;
	t_renderable_type				type;
	union
	{
		t_ray						*ray;
		t_sprite					*sprite;
		t_sprite_spawner			*spawner;
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
