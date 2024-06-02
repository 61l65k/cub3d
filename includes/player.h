/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:37:06 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 19:31:50 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "display.h"
# include <stdbool.h>

# define PLAYER_MAX_HEALTH 200
# define SPRITE_ATTACK_RANGE 0.5
# define SPRITE_BOSS_ATTACK_RANGE 1.2
# define TAKE_DAMAGE_DISPLAY_TIME 10.0
# define TAKE_DAMAGE_COOLDOWN_TIME 7.0

typedef struct s_cubed			t_cubed;
typedef struct s_sprite			t_sprite;
typedef struct s_sprite_boss	t_sprite_boss;

typedef struct s_player
{
	double						x;
	double						y;
	double						dir_x;
	double						dir_y;
	double						plane_x;
	double						plane_y;
	double						fov_rad;
	int							x_move;
	int							z_move;
	int							health;
	double						move_speed;
	int							turn_direction;
	double						rotation_angle;
	double						rotation_speed;
	bool						shooting;
	bool						taking_damage;
	int							damage_timer;
	double						damage_cooldown;
	t_health_bar				health_bar;
}								t_player;

void							check_sprite_hit_player(t_cubed *cubed,
									t_sprite *sprite);
void							prepare_player(t_cubed *cubed);
void							draw_take_damage(t_cubed *cubed);
void							clear_screen(t_cubed *cubed);
void							draw_game_over_screen(t_cubed *cubed);
void							check_boss_hit_player(t_cubed *cubed,
									t_sprite_boss *boss);

#endif
