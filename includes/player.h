/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:37:06 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 06:16:35 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdbool.h>

typedef struct s_cubed	t_cubed;
typedef struct s_sprite	t_sprite;

typedef struct s_player
{
	double				x;
	double				y;
	float				dir_x;
	float				dir_y;
	float				plane_x;
	float				plane_y;
	int					x_move;
	int					z_move;
	int					health;
	double				move_speed;
	int					turn_direction;
	double				rotation_angle;
	double				rotation_speed;
	bool				shooting;
	bool				taking_damage;
	int					damage_timer;
	double				damage_cooldown;
}						t_player;

void					check_sprite_hit_player(t_cubed *cubed,
							t_sprite *sprite);
void					prepare_player(t_cubed *cubed);
void					draw_take_damage(t_cubed *cubed);

#endif
