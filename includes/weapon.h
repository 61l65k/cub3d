/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:15:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 19:59:11 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

# include "display.h"

# define WEAPON_PATHS \
	"./assets/weapons/akimbos/akimbos.xpm:\
./assets/weapons/hammer/wwrench.xpm:\
./assets/weapons/raygun/raygun.xpm:\
./assets/weapons/minigun/minigunner.xpm"

# define W_ANIMATION_PATHS \
	"./assets/weapons/akimbos/cloud_fire0.xpm:\
./assets/weapons/akimbos/cloud_fire1.xpm:\
./assets/weapons/akimbos/cloud_fire2.xpm:\
./assets/weapons/hammer/cloud_magic_trail0.xpm:\
./assets/weapons/hammer/cloud_magic_trail1.xpm:\
./assets/weapons/hammer/cloud_magic_trail2.xpm:\
./assets/weapons/hammer/cloud_magic_trail3.xpm:\
./assets/weapons/raygun/cloud_poison0.xpm:\
./assets/weapons/raygun/cloud_poison1.xpm:\
./assets/weapons/raygun/cloud_poison2.xpm:\
./assets/weapons/minigun/cloud_fire0.xpm:\
./assets/weapons/minigun/cloud_fire1.xpm:\
./assets/weapons/minigun/cloud_fire2.xpm"

typedef struct s_cubed	t_cubed;

typedef enum e_weapon_range
{
	RANGE_AKIMBOS = 100,
	RANGE_RAYGUN = 1000,
	RANGE_MINIGUN = 300
}						t_weapon_range;

typedef enum e_weapon_dmg
{
	DMG_AKIMBOS = 80,
	DMG_RAYGUN = 50,
	DMG_MINIGUN = 2
}						t_weapon_dmg;

typedef enum e_weapon_type
{
	WEAPON_AKIMBOS,
	WEAPON_WRENCH,
	WEAPON_RAYGUN,
	WEAPON_MINIGUN,
	WEAPON_MAX
}						t_weapon_type;

typedef struct s_weapon
{
	t_texture			texture;
	t_animation			shooting_animation;
	int					gun_pos_x;
	int					gun_pos_y;
	int					left_gun_tip_x;
	int					right_gun_tip_x;
	int					gun_tip_y;
	int					damage;
	int					range;
	t_weapon_type		type;
}						t_weapon;

typedef struct s_weapon_map
{
	t_weapon			weapons[WEAPON_MAX];
	int					current_weapon;
}						t_weapon_map;

int						handle_weapon_switch(int button, t_cubed *cubed);
void					load_weapons(t_cubed *cubed, t_weapon_map *weapon_map);
void					get_gun_pos_dmg(t_weapon *weapon, t_cubed *cubed,
							int i);
void					handle_shooting(t_cubed *cubed);
void					draw_gun_shooting(t_cubed *cubed);

#endif
