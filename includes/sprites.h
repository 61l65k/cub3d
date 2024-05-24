/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:56:47 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 01:10:46 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "display.h"

typedef struct s_cubed	t_cubed;

typedef struct s_sprite
{
	double				x;
	double				y;
	double				distance;
	double				angle;
	t_texture			texture;
}						t_sprite;

typedef struct s_sprite_spawner
{
	double				x;
	double				y;
	t_texture			texture;
}						t_sprite_spawner;

typedef struct s_sprite_spawners
{
	t_sprite_spawner	*spawners;
	int					spawner_count;
}						t_sprite_info;

void					prepare_sprites(t_cubed *cubed);

#endif
