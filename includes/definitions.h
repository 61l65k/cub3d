/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:01:16 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 07:55:55 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define ARG_ERROR_MSG \
	"Remember to give the cub file name ./cub3d \
<example.cub>\n"
# define CUB_OPEN_ERROR_MSG "Error: .cub open()\n"
# define CUB_ERROR_COLOR \
	"Error: get_color_rgb()\
	- color value out of range\n"
# define CUB_ERROR_MALLOC "Error: malloc() in -> "
# define CUB_MAP_SPLIT_DELIMITERS " \n\t\v\f\r"
# define ERR_RGB "Error: get_color_rgb() - invalid rgb value\n"
# define ERR_RESOLUTION "Error: get_resolution() - invalid resolution value\n"
# define ERR_INVALID_EXTENSION "Error: invalid file extension %s\n"
# define ERR_POORLY_FORMATTED "Error: poorly formatted %s \n"
# define ERR_OPENTEXT "Error\nCould not open the %s: %s.\n"
# define ERR_MAP_NOT_SURROUNDED "Error: map is not surrounded by walls\n"
# define ERR_MISSING_MAP "Error: map is missing\n"
# define ERR_START_POSITION "Error: map has invalid start position\n"
# define VALID_CHARS "012NSEW "
# define GUN_TEXTURE_PATH "assets/gun/akimbos.xpm"
# define ERR_LOAD_WEAPON "Error: load_weapon() - could not load weapon\n"
# define ERR_LOAD_TEXTURE "Error: load_texture() - could not load texture\n"

# ifndef LINUX
#  define LINUX 0
# endif

# define LEFT_CLICK 1
# define RIGHT_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define GRID_UNIT_SCALE 64
# define MAX_X_RES 1000
# define MAX_Y_RES 500
# define FOV 60
# define TAB_SIZE 4
# ifndef linux
#  define K_ESC 53
#  define K_W 13
#  define K_A 0
#  define K_S 1
#  define K_D 2
#  define K_LEFT_ARROW 123
#  define K_RIGHT_ARROW 124
#  define K_SPACE 49
#  define K_M 46
# else
#  define K_ENTER 65293
#  define K_SPACE 32
#  define K_ESC 65307
#  define K_W 119
#  define K_A 97
#  define K_S 115
#  define K_D 100
#  define K_M 109
#  define K_LEFT_ARROW 65361
#  define K_RIGHT_ARROW 65363
#  define K_FORWARD_ARROW 65362
#  define K_BACK_ARROW 65364
# endif

# ifndef linux
#  define DESTROY_NOTIFY 17
#  define KEY_PRESS 02
#  define KEY_RELEASE 03
#  define M_DESTROY_NOTIFY 131072
#  define M_KEY_PRESS 1
#  define M_KEY_RELEASE 2
# else
#  define DESTROY_NOTIFY 33
#  define KEY_PRESS 02
#  define KEY_RELEASE 03
#  define M_DESTROY_NOTIFY 0
#  define M_KEY_PRESS 1
#  define M_KEY_RELEASE 2
# endif

#endif
