/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:15:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/23 13:55:31 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

# define MAX_WEAPONS 10
# include "display.h"

typedef struct s_cubed	t_cubed;

# define WEAPON_PATHS \
	"./assets/weapons/akimbos/akimbos.xpm:\
./assets/weapons/hammer/wwrench.xpm:\
./assets/weapons/raygun/raygun.xpm"

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
./assets/weapons/raygun/cloud_poison2.xpm"

typedef struct s_weapon
{
    t_texture            texture;
    t_animation          shooting_animation;
    int                  gun_pos_x;
    int                  gun_pos_y;
    int                  left_gun_tip_x;
    int                  right_gun_tip_x;
    int                  gun_tip_y;
}                       t_weapon;


typedef struct s_weapon_map
{
	t_weapon			weapons[MAX_WEAPONS];
	int					current_weapon;
	int					total_weapons;
}						t_weapon_map;

int						handle_weapon_switch(int button, t_cubed *cubed);
void					load_weapons(t_cubed *cubed, t_weapon_map *weapon_map);
#endif
