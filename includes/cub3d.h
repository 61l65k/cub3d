/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:02:10 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 09:23:02 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "datastructs.h"
# include "definitions.h"
# include "libft.h"
# include "utils.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum
{
	GAME_STATE_RUNNING,
	GAME_STATE_MENU
}					t_game_state;

typedef struct s_cubed
{
	t_game_state	game_state;
	t_scenedata		scene;
	t_mlx			mlx;
	t_rays			rays;
	t_player		player;
}					t_cubed;

void				validate_scene(t_cubed *cubed);
void				start_game(t_cubed *cubed);
void				prepare_textures(t_cubed *cubed);
void				prepare_rays(t_cubed *cubed);
void				prepare_player(t_cubed *cubed);
void				prepare_rays(t_cubed *cubed);
void				draw_floor(t_cubed *cubed);
void				draw_ceiling(t_cubed *cubed);
void				draw_walls(t_cubed *game);
void				cast_ray(t_ray *ray, t_map *map, t_player *player);
void				update_rays(t_cubed *game);
void				draw_gun_shooting(t_cubed *cubed);
void				draw_menu(t_cubed *cubed);
void				handle_shooting(t_cubed *cubed);

#endif