/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:02:10 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/06 17:04:31 by apyykone         ###   ########.fr       */
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

typedef struct s_cubed
{
	t_scenedata	scene;
	t_mlx		mlx;
}				t_cubed;

void			extract_scene(t_cubed *cubed, char **av);
void			extract_map(t_cubed *cubed, int fd, char *line);
void			validate_scene(t_cubed *cubed);
void			start_game(t_cubed *cubed);

#endif